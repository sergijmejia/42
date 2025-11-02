/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:53:50 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:00:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include "exec.h"
#include "libft.h"

/* ----------------------------------------
   Escribe las líneas del heredoc en fd_write
---------------------------------------- */
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

/* ----------------------------------------
   Prepara un heredoc y devuelve el fd de lectura
---------------------------------------- */
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

/* ----------------------------------------
   Ejecuta un heredoc standalone (caso sencillo)
---------------------------------------- */
void	exec_heredoc(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	int		fd;
	pid_t	pid;
	int		status;

	fd = exec_heredoc_prepare(node);
	if (fd == -1)
	{
		g_exit_status = 1;
		return ;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: heredoc fork");
		close(fd);
		g_exit_status = 1;
		return ;
	}

	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(fd, STDIN_FILENO) == -1)
			_exit(1);
		close(fd);
		exec_ast(node->left_ast, temp_vars, envp, parser_tmp_var);
		_exit(g_exit_status);
	}

	close(fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	else
		g_exit_status = 1;
}
