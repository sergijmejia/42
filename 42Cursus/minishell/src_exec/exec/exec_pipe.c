/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:54:32 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 11:22:29 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "exec.h"
#include "env.h"
#include "minishell.h"
#include "minishell_exec.h"
#include "exec_pipe_ctx.h"

/**
 * @brief Creates a pipe and handles errors.
 *
 * @param fd Array of two file descriptors
 * @return 1 on success, 0 on failure
 */
static int	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		write(2, "Pipe error\n", 11);
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

/**
 * @brief Forks and executes the left side of a pipe.
 *
 * @param node AST node for the left command
 * @param ctx Pipe context containing env, temp vars, parser tmp, and fd
 * @return PID of the created child
 */
static pid_t	fork_pipe_left(t_ast *node, t_pipe_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(ctx->fd[1], STDOUT_FILENO) == -1)
			_exit(1);
		close(ctx->fd[0]);
		close(ctx->fd[1]);
		exec_ast(node, ctx->temp_vars, ctx->envp, ctx->parser_tmp_var);
		free_envp(*ctx->envp);
		ft_lstclear(ctx->parser_tmp_var, free_tmp_var_p);
		free(ctx->parser_tmp_var);
		clean_ast(node);
		_exit(g_exit_status);
	}
	return (pid);
}

/**
 * @brief Forks and executes the right side of a pipe.
 *
 * @param node AST node for the right command
 * @param ctx Pipe context containing env, temp vars, parser tmp, and fd
 * @return PID of the created child
 */
static pid_t	fork_pipe_right(t_ast *node, t_pipe_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(ctx->fd[0], STDIN_FILENO) == -1)
			_exit(1);
		close(ctx->fd[0]);
		close(ctx->fd[1]);
		exec_ast(node, ctx->temp_vars, ctx->envp, ctx->parser_tmp_var);
		free_envp(*ctx->envp);
		ft_lstclear(ctx->parser_tmp_var, free_tmp_var_p);
		free(ctx->parser_tmp_var);
		clean_ast(node);
		_exit(g_exit_status);
	}
	return (pid);
}

/**
 * @brief Waits for both children and updates g_exit_status.
 *
 * @param pid_l PID of left child
 * @param pid_r PID of right child
 */
static void	wait_for_pipe(pid_t pid_l, pid_t pid_r)
{
	int	status_l;
	int	status_r;

	waitpid(pid_l, &status_l, 0);
	waitpid(pid_r, &status_r, 0);
	if (WIFEXITED(status_r))
		g_exit_status = WEXITSTATUS(status_r);
	else
		g_exit_status = 1;
}

/**
 * @brief Executes a pipe AST node like Bash.
 *
 * @param node AST node of type TOKEN_P_PIPE
 * @param temp_vars Temporary environment variable list
 * @param envp Pointer to environment array
 * @param parser_tmp_var Parser temporary variable table
 */
void	exec_pipe(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	t_pipe_ctx	ctx;
	pid_t		pid_left;
	pid_t		pid_right;

	if (!node)
		return ;
	ctx.temp_vars = temp_vars;
	ctx.envp = envp;
	ctx.parser_tmp_var = parser_tmp_var;
	if (!create_pipe(ctx.fd))
		return ;
	pid_left = fork_pipe_left(node->left_ast, &ctx);
	pid_right = fork_pipe_right(node->right_ast, &ctx);
	close(ctx.fd[0]);
	close(ctx.fd[1]);
	wait_for_pipe(pid_left, pid_right);
}
