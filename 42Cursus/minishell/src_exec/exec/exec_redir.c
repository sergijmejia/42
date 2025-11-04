/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:55:17 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:42:04 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_heredoc.h"
#include "minishell_exec.h"
#include "env.h"

/**
 * @brief Prepare heredoc or file descriptors for redirection.
 *
 * Handles both standalone heredocs and heredocs embedded
 * within another redirection or pipe.
 *
 * @param node AST node for redirection.
 * @param fd_in Pointer to input FD.
 * @param filename Pointer to filename.
 * @param ctx Execution context containing temp vars, envp, and parser vars.
 * @return 1 if successful, 0 if error (caller should return).
 */
static int	prepare_redir_fds(t_ast *node, int *fd_in, char **filename,
		t_exec_ctx *ctx)
{
	if (node->type == TOKEN_P_DOUBLE_LT)
	{
		if (!node->right_ast || !node->right_ast->left_ast)
		{
			exec_heredoc(node, ctx->temp_vars, ctx->envp, ctx->parser_tmp_var);
			return (0);
		}
		else
		{
			*fd_in = exec_heredoc_prepare(node->right_ast);
			if (*fd_in == -1)
			{
				g_exit_status = 1;
				return (0);
			}
			*filename = get_redir_filename_from_node(node->right_ast->left_ast);
		}
	}
	else
		*filename = get_redir_filename_from_node(node->right_ast);
	return (1);
}

/**
 * @brief Initialize and return a redirection context.
 *
 * Sets default fds and filename values, assigns execution pointers.
 *
 * @param node AST node to validate.
 * @param temp_vars Temporary variable list.
 * @param envp Pointer to the environment array.
 * @param parser_tmp_var Temporary parser variable list.
 * @return Initialized t_exec_ctx struct.
 */
static t_exec_ctx	init_redir_context(t_ast *node,
		t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var)
{
	t_exec_ctx	ctx;

	ctx.fd_in = -1;
	ctx.fd_out = -1;
	ctx.filename = NULL;
	ctx.temp_vars = temp_vars;
	ctx.envp = envp;
	ctx.parser_tmp_var = parser_tmp_var;
	ctx.valid = 1;
	if (!node || !node->left_ast)
	{
		g_exit_status = 1;
		ctx.valid = 0;
	}
	return (ctx);
}

/**
 * @brief Handle output redirection file opening and errors.
 *
 * Opens the output file depending on redirection type (>, >>),
 * and updates ctx.fd_out accordingly.
 *
 * @param node AST node representing the redirection.
 * @param ctx Pointer to the execution context.
 * @return 1 on success, 0 on failure.
 */
static int	handle_output_redir(t_ast *node, t_exec_ctx *ctx)
{
	ctx->filename = get_redir_filename_from_node(node->right_ast);
	if (!ctx->filename)
	{
		g_exit_status = 1;
		return (0);
	}
	ctx->fd_out = open_redir_file(ctx->filename, node->type);
	if (ctx->fd_out == -1)
	{
		perror(ctx->filename);
		g_exit_status = 1;
		if (ctx->fd_in != -1)
			close(ctx->fd_in);
		return (0);
	}
	return (1);
}

/**
 * @brief Initialize the redirection execution context.
 *
 * Sets default values for file descriptors and stores references
 * to the environment and temporary variables.  
 * Also validates the AST node before execution.
 *
 * @param node AST node containing the redirection information.
 * @param temp_vars Pointer to the temporary environment variable list.
 * @param envp Pointer to the environment array.
 * @param parser_tmp_var Pointer to the parser temporary variable list.
 * @return A fully initialized t_exec_ctx structure.
 *         If the node is invalid, ctx.valid is set to 0 and g_exit_status = 1.
 */
void	exec_redir(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	t_exec_ctx	ctx;

	ctx = init_redir_context(node, temp_vars, envp, parser_tmp_var);
	if (!ctx.valid)
		return ;
	if (!prepare_redir_fds(node, &ctx.fd_in, &ctx.filename, &ctx))
		return ;
	if (!ctx.filename && ctx.fd_in == -1)
	{
		g_exit_status = 1;
		return ;
	}
	if (node->type == TOKEN_P_GT || node->type == TOKEN_P_DOUBLE_GT
		|| node->type == TOKEN_P_LT)
	{
		if (!handle_output_redir(node, &ctx))
			return ;
	}
	exec_redir_child(ctx.fd_in, ctx.fd_out, node, &ctx);
}
