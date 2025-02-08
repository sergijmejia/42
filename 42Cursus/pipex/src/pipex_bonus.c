/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:58:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/08 17:44:15 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion que gestiona el parent (pid_in != 0)*/
static void	fst_parent(t_arguments a, int fd[2], int sv_err[2], int pipe[2])
{
	int		status;
	int		final_status;

	parent_multiple(fd, pipe, a, sv_err[1]);
	final_status = 0;
	while (wait(&status) > 0)
	{
		if (WEXITSTATUS(status) != 0)
			final_status = WEXITSTATUS(status);
	}
	if (final_status != 0)
	{
		if (ft_strncmp(a.argv[1], "here_doc", 9) == 0)
			unlink(".temp_pipex");
		exit(final_status);
	}
}

/*Funcion pipex*/
static int	ft_pipex(t_arguments arg, int fd_file[2], int saved_errno[2])
{
	int		fd_pipe[2];
	pid_t	pid_in;

	if (pipe(fd_pipe) == -1)
		ft_print_error();
	pid_in = fork();
	if (pid_in == -1)
		ft_print_error();
	if (pid_in == 0)
		first_child(fd_file[0], fd_pipe, saved_errno[0], arg);
	else
		fst_parent(arg, fd_file, saved_errno, fd_pipe);
	unlink(".temp_pipex");
	return (1);
}

/*Funcion que crea el archivo temporal y almacena la informacion introducida
mediante heredoc*/
static void	create_complete_file(t_arguments arg)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open(".tmp_pipex", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_print_error();
	ft_printf("pipe heredoc> ");
	line = get_next_line(0);
	len = ft_strlen(line);
	while (ft_strncmp(line, arg.argv[2], len - 1) || line[0] == '\n')
	{
		ft_putstr_fd(line, fd);
		free(line);
		ft_printf("pipe heredoc> ");
		line = get_next_line(0);
		len = ft_strlen(line);
	}
	free(line);
	close(fd);
}

/*Funcion que inicializa los fd de los archivos y gestiona la funcion fd_pipex*/
static int	initialize(t_arguments arg)
{
	int		fd_file[2];
	int		saved_errno[2];
	char	*exit_file;

	saved_errno[0] = 0;
	saved_errno[1] = 0;
	exit_file = arg.argv[arg.argc - 1];
	if (ft_strncmp(arg.argv[1], "here_doc", 9) == 0)
	{
		create_complete_file(arg);
		fd_file[0] = open(".tmp_pipex", O_RDONLY);
		if (fd_file[0] == -1)
			saved_errno[0] = errno;
	}
	else
	{
		fd_file[0] = open(arg.argv[1], O_RDONLY);
		if (fd_file[0] == -1)
			saved_errno[0] = errno;
	}
	fd_file[1] = open(exit_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file[1] == -1)
		saved_errno[1] = errno;
	return (ft_pipex(arg, fd_file, saved_errno));
}

/*Programa main principal*/
int	main(int argc, char **argv, char **envp)
{
	t_arguments	arg;

	errno = 0;
	if (argc < 5)
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
