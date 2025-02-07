/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:11:49 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/07 13:20:01 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion hijo que lee el file1 y escribe en el pipe entre los comandos*/
static void	file_pipe(int fd_in, int fd_pipe[2], t_arguments arg)
{
	char	**cmd_args;

	close(fd_pipe[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_print_error();
	close(fd_in);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		ft_print_error();
	close(fd_pipe[1]);
	cmd_args = ft_split(arg.argv[2], ' ');
	if (cmd_args == NULL)
		ft_print_error();
	execute_command(cmd_args, arg.envp);
}

/*Funcion hijo que lee del pipe entre comandos y escribe en el file2*/
static void	pipe_file(int fd_out, int fd_pipe, t_arguments arg)
{
	char	**cmd_args;
	char	*last_cmd;

	if (dup2(fd_pipe, STDIN_FILENO) == -1)
		ft_print_error();
	close(fd_pipe);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_print_error();
	close(fd_out);
	last_cmd = arg.argv[arg.argc - 2];
	cmd_args = ft_split(last_cmd, ' ');
	if (cmd_args == NULL)
		ft_print_error();
	execute_command(cmd_args, arg.envp);
}

/*Funcion padre*/
void	parent(int fd_file[2], int fd_pipe[2], t_arguments arg)
{
	pid_t	pid_out;
	int		status;
	int		exit_code;

	if (fd_file[0] != -1)
		close(fd_file[0]);
	close(fd_pipe[1]);
	pid_out = fork();
	if (pid_out == -1)
		ft_print_error();
	if (pid_out == 0)
		pipe_file(fd_file[1], fd_pipe[0], arg);
	else
	{
		close(fd_pipe[0]);
		waitpid(pid_out, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			exit(exit_code);
		close(fd_file[1]);
	}
}

/*Funcion que maneja el proceso hijo*/
void	child(int fd, int pipe[2], int saved_errno, t_arguments arg)
{
	if (fd == -1)
		exit(ft_print_file_error(arg.argv[1], saved_errno));
	file_pipe(fd, pipe, arg);
}
