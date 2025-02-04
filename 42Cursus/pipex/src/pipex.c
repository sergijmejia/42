/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:58:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/04 18:45:01 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion de libearacion de memoria del split*/
static char	*ft_clean_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}

/*Obtener la ruta del comando*/
static char	*get_cmd_path(char *argv, char **envp)
{
	int		i;
	char	**str_split;
	char	*str;
	char	*str_tmp;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	str_split = ft_split(envp[i] + 5, ':');
	if (str_split == NULL)
		return (NULL);
	i = 0;
	while (str_split[i] != NULL)
	{
		str_tmp = ft_strjoin(str_split[i], "/");
		if (str_tmp == NULL)
		{
			ft_clean_split(str_split);
			return (NULL);
		}
		str = ft_strjoin(str_tmp, argv);
		if (str == NULL || access(str, X_OK) == 0)
		{
			free(str_tmp);
			ft_clean_split(str_split);
			return (str);
		}
		free(str_tmp);
		free(str);
		i++;
	}
	ft_clean_split(str_split);
	return (NULL);
}

/*Funcion hijo que lee el file1 y escribe en el pipe entre los comandos*/
static void	file_pipe(int fd_in, int fd_pipe[2], char **argv, char **envp)
{
	char	**str_split1;
	char	*cmd1;

	close(fd_pipe[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_print_error();
	close(fd_in);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		ft_print_error();
	close(fd_pipe[1]);
	str_split1 = ft_split(argv[2], ' ');
	if (str_split1 == NULL)
		ft_print_error();
	cmd1 = get_cmd_path(str_split1[0], envp);
	if (cmd1 == NULL)
	{
		free(cmd1);
		ft_clean_split(str_split1);
		errno = ENOENT;
		ft_print_command_error(argv[2]);
	}
	if (execve(cmd1, str_split1, NULL) == -1)
	{
		free(cmd1);
		ft_clean_split(str_split1);
		if (errno == EACCES)
			ft_print_command_error(argv[2]);
		else
			ft_print_error();
	}
}

/*Funcion hijo que lee del pipe entre comandos y escribe en el file2*/
static void	pipe_file(int fd_out, int fd_pipe[2], char **argv, char **envp)
{
	char	**str_split2;
	char	*cmd2;

	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		ft_print_error();
	close(fd_pipe[0]);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_print_error();
	close(fd_out);
	str_split2 = ft_split(argv[3], ' ');
	if (str_split2 == NULL)
		ft_print_error();
	cmd2 = get_cmd_path(str_split2[0], envp);
	if (cmd2 == NULL)
	{
		free(cmd2);
		ft_clean_split(str_split2);
		errno = ENOENT;
		ft_print_command_error(argv[3]);
	}
	if (execve(cmd2, str_split2, NULL) == -1)
	{
		free(cmd2);
		ft_clean_split(str_split2);
		if (errno == EACCES)
			ft_print_command_error(argv[2]);
		else
			ft_print_error();
	}
}

/*Funcion padre*/
static int	parent(int fd_out, int fd_pipe[2], char **argv, char **envp)
{
	pid_t	pid_out;
	int		status;
	int		exit_code;

	close(fd_pipe[1]);
	pid_out = fork();
	if (pid_out == -1)
		ft_print_error();
	if (pid_out == 0)
		pipe_file(fd_out, fd_pipe, argv, envp);
	else
	{
		close(fd_pipe[0]);
		waitpid(pid_out, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			exit(exit_code);
		close(fd_out);
	}
	return (1);
}

/*Funcion que */

/*Funcion pipex*/
static int	ft_pipex(char **argv, char **envp, int fd_file[2], int saved_errno[2])
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
	{
		if (fd_file[0] == -1)
			ft_print_file_error(argv[1], saved_errno[0]);
		file_pipe(fd_file[0], fd_pipe, argv, envp);
	}
	else
	{
		if (fd_file[1] == -1)
			ft_print_file_error(argv[4], saved_errno[1]);
		if (fd_file[0] != -1)
			close(fd_file[0]);
		parent(fd_file[1], fd_pipe, argv, envp);
		waitpid(pid_in, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit(WEXITSTATUS(status));
		close(fd_file[0]);
		close(fd_file[1]);
	}
	return (1);
}

/*Funcion que inicializa los fd de los archivos y gestiona la funcion fd_pipex*/
static int	initialize(char **argv, char **envp)
{
	int	fd_file[2];
	int	saved_errno[2];
	
	if (fd_file[0] == -1)
		saved_errno[0] = errno;
	fd_file[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file[1] == -1)
		saved_errno[1] = errno;
	ft_pipex(argv, envp, fd_file, saved_errno);
	return (1);
}

/*Programa main principal*/
int	main(int argc, char **argv, char **envp)
{
	errno = 0;
	if (argc != 5)
	{
		errno = EINVAL;
		ft_print_error();
	}
	if (initialize(argv, envp) == 1)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
