/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:58:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/07 13:56:10 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion pipex*/
static int	ft_pipex(t_arguments arg, int fd_file[2], int saved_errno[2])
{
	int		fd_pipe[2];
	int		status;
	pid_t	pid_in;

	if (pipe(fd_pipe) == -1)
		ft_print_error();
	pid_in = fork();
	if (pid_in == -1)
		ft_print_error();
	if (pid_in == 0)
		child(fd_file[0], fd_pipe, saved_errno[0], arg);
	else
	{
		if (fd_file[1] == -1)
			exit(ft_print_file_error(arg.argv[4], saved_errno[1]));
		parent(fd_file, fd_pipe, arg);
		waitpid(pid_in, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit(WEXITSTATUS(status));
		close(fd_file[0]);
		close(fd_file[1]);
	}
	return (1);
}

/*Funcion que inicializa los fd de los archivos y gestiona la funcion fd_pipex*/
static int	initialize(t_arguments arg)
{
	int	fd_file[2];
	int	saved_errno[2];

	saved_errno[0] = 0;
	saved_errno[1] = 0;
	fd_file[0] = open(arg.argv[1], O_RDONLY);
	if (fd_file[0] == -1)
		saved_errno[0] = errno;
	fd_file[1] = open(arg.argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file[1] == -1)
		saved_errno[1] = errno;
	return (ft_pipex(arg, fd_file, saved_errno));
}

/*Programa main principal*/
int	main(int argc, char **argv, char **envp)
{
	t_arguments	arg;

	errno = 0;
	if (argc != 5)
	{
		errno = EINVAL;
		ft_print_error();
	}
	arg.argc = argc;
	arg.argv = argv;
	arg.envp = envp;
	if (initialize(arg) == 1)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
