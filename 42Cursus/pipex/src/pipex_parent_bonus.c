/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parent_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:20:14 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/07 19:56:41 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion hijo que lee del pipe entre comandos y escribe en el file2*/
void	pipe_file(int fd_out, int fd_pipe, t_arguments arg)
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

/*Funcion hijo que lee de un pipe entre comandos y escribe a otro pipe entre
comandos*/
static void	pipe_pipe(t_arguments arg, int i, int fd_in, int fd_pipe_out[2])
{
	char	**cmd_args;

	close(fd_pipe_out[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_print_error();
	close(fd_in);
	if (dup2(fd_pipe_out[1], STDOUT_FILENO) == -1)
		ft_print_error();
	close(fd_pipe_out[1]);
	cmd_args = ft_split(arg.argv[i + 3], ' ');
	if (cmd_args == NULL)
		ft_print_error();
	execute_command(cmd_args, arg.envp);
}

/*Funcion hijo intermedio*/
int	internal_child(t_arguments arg, int i, int fd_pipe_in)
{
	pid_t	pid_cmd;
	int		fd_pipe_out[2];

	if (pipe(fd_pipe_out) == -1)
		ft_print_error();
	pid_cmd = fork();
	if (pid_cmd == -1)
		ft_print_error();
	if (pid_cmd == 0)
		pipe_pipe(arg, i, fd_pipe_in, fd_pipe_out);
	else
	{
		close(fd_pipe_in);
		close(fd_pipe_out[1]);
	}
	return (fd_pipe_out[0]);
}

/*Funcion padre cuando se hace el fork para el ultimo hijo*/
static void	parent_out(int fd_file_out, int fd_pipe_in, t_arguments arg)
{
	pid_t	pid_out;

	pid_out = fork();
	if (pid_out == -1)
		ft_print_error();
	if (pid_out == 0)
		pipe_file(fd_file_out, fd_pipe_in, arg);
	else
	{
		close(fd_pipe_in);
		close(fd_file_out);
	}
}

/*Funcion padre*/
void	parent_multiple(int fd_file[2], int fd_pipe[2], t_arguments arg)
{
	int		i;
	int		fd_pipe_in;

	if (fd_file[0] != -1)
		close(fd_file[0]);
	close(fd_pipe[1]);
	fd_pipe_in = fd_pipe[0];
	if (ft_strncmp(arg.argv[1], "here_doc", 8) == 0)
		i = 1;
	else
		i = 0;
	while (i < (arg.argc - 5))
	{
		fd_pipe_in = internal_child(arg, i, fd_pipe_in);
		i++;
	}
	parent_out(fd_file[1], fd_pipe_in, arg);
}
