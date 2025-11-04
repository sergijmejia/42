/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:53:50 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:31:19 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include "env.h"
#include "exec.h"
#include "libft.h"
#include "minishell.h"

/*
 * @brief: write the lines of heredoc into fd_write
 */
static void	write_heredoc_lines(char **lines, int fd_write)
{
	int	i;

	if (!lines)
		return ;
	i = -1;
	while (lines[++i])
		write(fd_write, lines[i], ft_strlen(lines[i]));
	close(fd_write);
}

/*
 * @brief: prepares a heredoc and returns the fd to read from
 */
int	exec_heredoc_prepare(t_ast *node)
{
	int	hd[2];

	if (!node || !node->right_ast || !node->right_ast->value)
		return (-1);
	if (pipe(hd) == -1)
	{
		perror("minishell: heredoc pipe");
		return (-1);
	}
	write_heredoc_lines(node->right_ast->value, hd[1]);
	return (hd[0]);
}

/**
 * @brief Set default signals and redirect stdin for heredoc child.
 *
 * @param fd File descriptor to duplicate to STDIN_FILENO.
 * @note Exits the process with code 1 on error.
 */
static void	run_heredoc_child(int fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (dup2(fd, STDIN_FILENO) == -1)
		_exit(1);
	close(fd);
}

/**
 * @brief Update global exit status after waiting for heredoc child.
 *
 * @param pid Process ID of the heredoc child.
 */
static void	wait_heredoc_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	else
		g_exit_status = 1;
}

/**
 * @brief Execute heredoc: prepare, fork, run child, and update exit status.
 *
 * @param node AST node describing the heredoc redirection.
 * @param temp_vars Pointer to temporary variables list.
 * @param envp Pointer to environment array pointer.
 * @param parser_tmp_var Parser temporary variables list.
 * @note On failure sets g_exit_status = 1.
 */
void	exec_heredoc(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	int		fd;
	pid_t	pid;

	fd = exec_heredoc_prepare(node);
	if (fd == -1)
		return ((void)(g_exit_status = 1));
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: heredoc fork");
		close(fd);
		return ((void)(g_exit_status = 1));
	}
	if (pid == 0)
	{
		run_heredoc_child(fd);
		exec_ast(node->left_ast, temp_vars, envp, parser_tmp_var);
		free_envp(*envp);
		ft_lstclear(parser_tmp_var, free_tmp_var_p);
		free(parser_tmp_var);
		clean_ast(node);
		_exit(g_exit_status);
	}
	close(fd);
	wait_heredoc_child(pid);
}
