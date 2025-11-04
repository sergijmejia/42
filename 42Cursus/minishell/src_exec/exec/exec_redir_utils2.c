/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:52:25 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 01:52:26 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "minishell.h"
#include "minishell_exec.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/**
 * @brief Apply a redirection to STDIN or STDOUT.
 *
 * @param fd File descriptor.
 * @param type Token type (>, >>, <).
 */
void	apply_redirection(int fd, int type)
{
	if (type == TOKEN_P_GT || type == TOKEN_P_DOUBLE_GT)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			_exit(1);
	}
	else if (type == TOKEN_P_LT)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			_exit(1);
	}
}

/**
 * @brief Configure and execute child for a redirection command.
 *
 * Restores default signals, applies redirections, and executes
 * the left AST branch.
 *
 * @param fd_in Input file descriptor.
 * @param fd_out Output file descriptor.
 * @param node AST node containing the command.
 * @param ctx Execution context (env, vars, etc.).
 */
void	exec_redir_run_child(int fd_in, int fd_out,
		t_ast *node, t_exec_ctx *ctx)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -1)
	{
		apply_redirection(fd_out, node->type);
		close(fd_out);
	}
	exec_ast(node->left_ast, ctx->temp_vars, ctx->envp, ctx->parser_tmp_var);
	_exit(g_exit_status);
}

/**
 * @brief Fork and handle redirection child process.
 *
 * @param fd_in Input file descriptor.
 * @param fd_out Output file descriptor.
 * @param node AST node.
 * @param ctx Execution context.
 */
void	exec_redir_child(int fd_in, int fd_out,
		t_ast *node, t_exec_ctx *ctx)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exec_redir_run_child(fd_in, fd_out, node, ctx);
		free_envp(*ctx->envp);
		ft_lstclear(ctx->parser_tmp_var, free_tmp_var_p);
		free(ctx->parser_tmp_var);
		clean_ast(node);
	}
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 130;
}
