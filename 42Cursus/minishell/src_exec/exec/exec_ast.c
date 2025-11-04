/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti@student.42barcelon>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:15:19 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 20:11:21 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell_exec.h"
#include "env.h"
#include "exec.h"
#include "libft.h"
#include "builtins.h"
#include "exec_logic.h"
#include "exec_search.h"
#include "exec_command_utils.h"

/**
 * @brief Executes a chain of assignment nodes, optionally with command.
 */
static void	exec_assignment_block(t_ast *node, t_exec_ctx *ctx)
{
	char	**env_for_exec;
	int		has_cmd;

	env_for_exec = NULL;
	has_cmd = has_command_in_assignment(node);
	if (has_cmd)
		env_for_exec = build_envp(*ctx->temp_vars, *ctx->envp);
	exec_assignment_chain(node, ctx, &env_for_exec);
	if (has_cmd && node->right_ast
		&& node->right_ast->type == TOKEN_P_COMMAND)
		fork_and_exec(node->right_ast, env_for_exec);
	if (env_for_exec)
		free_envp(env_for_exec);
	g_exit_status = 0;
}

/**
 * @brief Executes simple AST nodes: assignments, commands, pipes, redirections.
 */
static void	exec_ast_simple(t_ast *node, t_exec_ctx *ctx)
{
	if (!node)
	{
		g_exit_status = 0;
		return ;
	}
	if (node->type == TOKEN_P_ASSIGNMENT)
		exec_assignment_block(node, ctx);
	else if (node->type == TOKEN_P_COMMAND)
		exec_command(node, ctx->temp_vars, ctx->envp, ctx->parser_tmp_var);
	else if (node->type == TOKEN_P_PIPE)
		exec_pipe(node, ctx->temp_vars, ctx->envp, ctx->parser_tmp_var);
	else if (node->type == TOKEN_P_GT || node->type == TOKEN_P_DOUBLE_GT
		|| node->type == TOKEN_P_LT || node->type == TOKEN_P_DOUBLE_LT)
		exec_redir(node, ctx->temp_vars, ctx->envp, ctx->parser_tmp_var);
	else
	{
		ft_putendl_fd("minishell: syntax error: unsupported construct", 2);
		g_exit_status = 1;
	}
}

/**
 * @brief Executes an AST node by dispatching according to type.
 */
void	exec_ast(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***env, t_list **parser_tmp_var)
{
	t_exec_ctx	ctx;

	ctx.temp_vars = temp_vars;
	ctx.envp = env;
	ctx.parser_tmp_var = parser_tmp_var;
	ctx.fd_in = 0;
	ctx.fd_out = 1;
	ctx.filename = NULL;
	ctx.valid = 1;
	if (!node)
	{
		g_exit_status = 0;
		return ;
	}
	if (node->type == TOKEN_P_AND)
		exec_and(node, temp_vars, env, parser_tmp_var);
	else if (node->type == TOKEN_P_OR)
		exec_or(node, temp_vars, env, parser_tmp_var);
	else if (node->type == TOKEN_P_PARENTHESIS)
		exec_parenthesis(node, temp_vars, env, parser_tmp_var);
	else
		exec_ast_simple(node, &ctx);
}
