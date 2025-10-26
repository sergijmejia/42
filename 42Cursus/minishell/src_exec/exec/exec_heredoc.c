/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:53:50 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 11:34:20 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "exec.h"
#include "exec_heredoc.h"
#include "libft.h"

/**
 * @brief Writes heredoc content to the write end of a pipe.
 *
 * @param content The string content of the heredoc.
 * @param hd Pipe file descriptors array (fd[0] read, fd[1] write).
 */
static void	write_heredoc(const char *content, int hd[2])
{
	int	i;

	i = 0;
	while (content[i])
		write(hd[1], &content[i++], 1);
	write(hd[1], "\n", 1);
	close(hd[1]);
}

/**
 * @brief Forks a child process to execute the left AST node with stdin
 *        redirected from the heredoc pipe.
 *
 * Uses the t_heredoc_ctx structure to pass all required parameters.
 *
 * @param node AST node for the command to execute.
 * @param ctx Pointer to heredoc context (env, temp vars, parser tmp, pipe).
 */
static void	fork_exec_heredoc(t_ast *node, t_heredoc_ctx *ctx)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(ctx->hd[0], STDIN_FILENO) == -1)
			_exit(1);
		close(ctx->hd[0]);
		exec_ast(node->left_ast, ctx->temp_vars,
			ctx->envp, ctx->parser_tmp_var);
		_exit(g_exit_status);
	}
	close(ctx->hd[0]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	else
		g_exit_status = 1;
}

/**
 * @brief Executes a heredoc redirection node (<<).
 *
 * Creates a pipe, writes the heredoc content, and forks a child to execute
 * the command with stdin redirected from the pipe.
 *
 * @param node AST node of type TOKEN_P_DOUBLE_LT.
 * @param temp_vars Pointer to temporary environment variable list.
 * @param envp Pointer to the environment array.
 * @param parser_tmp_var Parser's temporary variable table.
 *
 * @note Updates the global g_exit_status.
 */
void	exec_heredoc(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	t_heredoc_ctx	ctx;

	if (pipe(ctx.hd) == -1)
	{
		write(2, "minishell: Heredoc pipe error\n", 30);
		g_exit_status = 1;
		return ;
	}
	ctx.temp_vars = temp_vars;
	ctx.envp = envp;
	ctx.parser_tmp_var = parser_tmp_var;
	write_heredoc(node->right_ast->value[0], ctx.hd);
	fork_exec_heredoc(node, &ctx);
}
