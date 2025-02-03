/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:58:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/03 18:57:27 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion que imprime el error*/
static void	print_error(char *str, int exit_code)
{
	char	*str_error_to_print;
	int		len;
	int		saved_errno;

	saved_errno = errno;
	//write(2, "Entrada en 1", 12);
	str_error_to_print = ft_strjoin(str, "\n");
	if (str_error_to_print == NULL)
	{
		errno = saved_errno;
		exit(exit_code);
	}
	len = (int) ft_strlen(str_error_to_print);
	if (write(2, str_error_to_print, len) == -1)
		errno = saved_errno;
	exit(exit_code);
}

/*Funcion para imprimir los errores de comandos no encontrados*/
static void	command_not_found_error(char *cmd)
{
	char	*str_error;
	int		saved_errno;
	int		exit_code;

	saved_errno = errno;
	//write(2, "Entrada en 2", 12);
	exit_code = 127;
	str_error = ft_strjoin("command not found: ", cmd);
	if (str_error == NULL)
	{
		errno = saved_errno;
		exit(exit_code);
	}
	print_error(str_error, exit_code);
}

/*Funcion para imprimir los errores de archivos no encontrados*/
static void	file_not_found_error(char *file)
{
	char	*str_error;
	int		saved_errno;
	int		exit_code;

	saved_errno = errno;
	//write(2, "Entrada en 3", 12);
	exit_code = 127;
	str_error = ft_strjoin("not such file or directory: ", file);
	if (str_error == NULL)
	{
		errno = saved_errno;
		exit(exit_code);
	}
	print_error(str_error, exit_code);
}


/*Funcion para imprimir los errores de comandos o archivos sin permisos*/
static void	permission_denied_error(char *str)
{
	char	*str_error;
	int		saved_errno;
	int		exit_code;

	saved_errno = errno;
	//write(2, "Entrada en 4", 12);
	exit_code = 126;
	str_error = ft_strjoin("permission denied: ", str);
	if (str_error == NULL)
	{
		errno = saved_errno;
		exit(exit_code);
	}
	print_error(str_error, exit_code);
}

/*Funcion para imprimir los errores de archivos cuando el nombre corresponde a
una carpeta*/
static void	is_directory_error(char *file)
{
	char	*str_error;
	int		saved_errno;
	int		exit_code;

	saved_errno = errno;
	exit_code = 21;
	str_error = ft_strjoin("is a directory: ", file);
	if (str_error == NULL)
	{
		errno = saved_errno;
		exit(exit_code);
	}
	print_error(str_error, exit_code);
}

/*Funcion para mostrar por su canal correspondiente los mensajes de error de
comandos*/
static void	ft_print_command_error(char *cmd)
{
	//write(2, "Entrada en 6", 12);
	if (errno == 2)
		command_not_found_error(cmd);
	else if (errno == 13)
		permission_denied_error(cmd);
	else
		exit(EXIT_FAILURE);
}

/*Funcion para mostrar por su canal correspondiente los mensajes de error de
archivos*/
static void	ft_print_file_error(char *file)
{
	//write(2, "Entrada en 7", 12);
	if (errno == 2)
		file_not_found_error(file);
	else if (errno == 13)
		permission_denied_error(file);
	else if (errno == 21)
		is_directory_error(file);
	else
		exit(EXIT_FAILURE);
}

/*Funcion para mostrar por s canal correspondiente los mensajes de error 
internos*/
static void	ft_print_error(void)
{
	char	*str_error;
	char	*str_error_to_print;
	int		len;
	int		saved_errno;

	//write(2, "Entrada en 8", 12);
	//ft_printf("%s\n", str);
	saved_errno = errno;
	str_error = strerror(errno);
	if (str_error == NULL)
	{
		errno = saved_errno;
		exit(EXIT_FAILURE);
	}
	str_error_to_print = ft_strjoin(str_error, "\n");
	if (str_error_to_print == NULL)
	{
		errno = saved_errno;
		exit(EXIT_FAILURE);
	}
	len = (int) ft_strlen(str_error_to_print);
	if (write (2, str_error_to_print, len) == -1)
		errno = saved_errno;
	exit(EXIT_FAILURE);
}

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
		str = ft_strjoin(ft_strjoin(str_split[i], "/"), argv);
		if (str == NULL || access(str, X_OK) == 0)
		{
			ft_clean_split(str_split);
			return (str);
		}
		free(str);
		i++;
	}
	return (ft_clean_split(str_split));
}

/*Funcion hijo que lee el file1 y escribe en el pipe entre los comandos*/
static int	file_pipe(int fd_in, int fd_pipe[2], char **argv, char **envp)
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
		errno = ENOENT;
		ft_print_command_error(argv[2]);
	}
	if (execve(cmd1, str_split1, NULL) == -1)
	{
		if (errno == EACCES)
			ft_print_command_error(argv[2]);
		else
			ft_print_error();
	}
	return (1);
}

/*Funcion hijo que lee del pipe entre comandos y escribe en el file2*/
static int	pipe_file(int fd_out, int fd_pipe[2], char **argv, char **envp)
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
		errno = ENOENT;
		ft_print_command_error(argv[3]);
	}
	if (execve(cmd2, str_split2, NULL) == -1)
		ft_print_error();
	return (1);
}

/*Funcion padre*/
static int	parent(int fd_in, int fd_out, int fd_pipe[2], char **argv, char **envp)
{
	pid_t	pid_out;
	int		status;
	int		exit_code;

	close(fd_pipe[1]);
	close(fd_in);
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

/*Funcion pipex*/
int	ft_pipex(char **argv, char **envp)
{
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	int		status;
	int		exit_code;
	pid_t	pid_in;

	errno = 0;
	if (pipe(fd_pipe) == -1)
		ft_print_error();
	pid_in = fork();
	if (pid_in == -1)
		ft_print_error();
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)  //el error esta en esto porque esta creando un archivo y cambiando fd_in
		fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pid_in == 0)
	{
		if (fd_in == -1)
			ft_print_file_error(argv[1]);
		file_pipe(fd_in, fd_pipe, argv, envp);
	}
	else
	{
		if (fd_out == -1)
			ft_print_file_error(argv[4]);
		parent(fd_in, fd_out, fd_pipe, argv, envp);
		waitpid(pid_in, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			exit(exit_code);
		close(fd_in);
		close(fd_out);
	}
	return (1);
}

/*Programa para conocer los codigos de error de zsh
void	print_errno()
{
	char	*str_error;
	char	*str_error_to_print;
	int		len;

	errno = 1;
	while(errno <= 255)
	{
		str_error = strerror(errno);
		str_error_to_print = ft_strjoin(str_error, "\n");
		len = ft_strlen(str_error_to_print);
		fprintf(stderr, "%d ", errno);
		write(2, str_error_to_print, len);

		free(str_error_to_print);
		errno++;
	}
}*/

/*Programa main principal*/
int	main(int argc, char **argv, char **envp)
{
	errno = 0;
	if (argc != 5)
	{
		errno = EINVAL;
		ft_print_error();
	}
	//print_errno();
	if (ft_pipex(argv, envp) == 1)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
