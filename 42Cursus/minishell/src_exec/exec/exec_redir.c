/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:55:17 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 11:44:39 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "exec.h"
#include "minishell_exec.h"
#include "env.h"

/**
 * @brief Opens a file for redirection.
 *
 * Supports the following types:
 * - TOKEN_P_GT         : Overwrite redirection (>)
 * - TOKEN_P_DOUBLE_GT  : Append redirection (>>)
 * - TOKEN_P_LT         : Input redirection (<)
 *
 * @param filename Path of the target file.
 * @param type Redirection operator token.
 * @return File descriptor on success, or -1 on failure.
 */
static int	open_redir_file(char *filename, int type)
{
	int	flags;

	if (!filename)
		return (-1);
	flags = 0;
	if (type == TOKEN_P_GT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (type == TOKEN_P_DOUBLE_GT)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (type == TOKEN_P_LT)
		flags = O_RDONLY;
	else
		return (-1);
	return (open(filename, flags, 0644));
}

/**
 * @brief Applies the given redirection to the current process.
 *
 * Redirects STDOUT or STDIN depending on the redirection type.
 * Exits the child process on failure.
 *
 * @param fd File descriptor to redirect.
 * @param type Type of redirection token.
 */
static void	apply_redirection(int fd, int type)
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
 * @brief Executes the redirection inside a child process.
 *
 * Handles signal reset to default behavior, applies redirection using dup2(),
 * then executes the left side of the AST (the actual command).
 *
 * @param fd File descriptor to be redirected.
 * @param node AST node representing the redirection.
 * @param ctx Execution context containing environment and temp vars.
 */
static void	exec_redir_child(int fd, t_ast *node, t_exec_ctx *ctx)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		apply_redirection(fd, node->type);
		close(fd);
		exec_ast(node->left_ast, ctx->temp_vars,
			ctx->envp, ctx->parser_tmp_var);
		_exit(g_exit_status);
	}
	close(fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 130;
}

/**
 * @brief Main entry point for executing a redirection AST node.
 *
 * Handles input/output redirections and heredocs.
 *
 * @param node AST node that represents a redirection type.
 * @param temp_vars Pointer to temporary environment variable list.
 * @param envp Pointer to environment variable array.
 * @param parser_tmp_var Parser's temporary variable table.
 */
void	exec_redir(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	int			fd;
	char		*filename;
	t_exec_ctx	ctx;

	if (!node || !node->left_ast || !node->value)
		return ((void)(g_exit_status = 1));
	if (node->right_ast && node->right_ast->value)
		filename = node->right_ast->value[0];
	else
		return ((void)(g_exit_status = 1));
	if (!filename)
		return ((void)(g_exit_status = 1));
	if (node->type == TOKEN_P_DOUBLE_LT)
		return (exec_heredoc(node, temp_vars, envp, parser_tmp_var));
	fd = open_redir_file(filename, node->type);
	if (fd == -1)
	{
		perror(filename);
		g_exit_status = 1;
		return ;
	}
	ctx.temp_vars = temp_vars;
	ctx.envp = envp;
	ctx.parser_tmp_var = parser_tmp_var;
	exec_redir_child(fd, node, &ctx);
}
