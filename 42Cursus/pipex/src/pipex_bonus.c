/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:58:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/29 15:41:57 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion para mostrar por su canal correspondiente los mensajes de error*/
void	ft_print_error(void)
{
	char	*str_error;
	int		len;

	str_error = strerror(errno);
	str_error = ft_strjoin(str_error, "\n");
	len = (int) ft_strlen(str_error);
	write (2, str_error, len);
	free(str_error);
}

/*Funcion de libearacion de memoria del split*/
char	*ft_clean_split(char **str)
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
char	*get_cmd_path(char *argv, char **envp)
{
	int		i;
	char	**str_split;
	char	*str;

	if (argv == NULL)
		return (NULL);
	if (access(argv, X_OK) == 0)
		return (argv);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	str_split = ft_split(envp[i] + 5, ':');
	if (str_split == NULL)
		return (NULL);
	while (str_split[i] != NULL)
	{
		str = ft_strjoin(ft_strjoin(str_split[i], "/"), argv);
		if (str == NULL || access(str, X_OK) == 0)
		{
			ft_clean_split(str_split);
			return (str);
		}
		//ft_printf("Esta entrando una vezi, el str_split es: %s\n", str_split[i]);
		//ft_printf("El argv es: %s\n", argv);
		free(str);
		i++;
	}
	return (ft_clean_split(str_split));
}

/*Funcion hijo que lee el file1 y escribe en el pipe entre los comandos*/
int	file_pipe(int fd_in, int fd_pipe[2], char **argv, char **envp)
{
	char	**str_split1;
	char	*cmd1;

	close(fd_pipe[0]);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	str_split1 = ft_split(argv[2], ' ');
	if (str_split1 == NULL)
	{
		//perror("Error al hacer split");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	cmd1 = get_cmd_path(str_split1[0], envp);
	fprintf(stderr, "%s\n", cmd1);  			//orden de impresion
	/*if (cmd1 == NULL)
	{
		perror("Error al localizar comando1");
		exit(EXIT_FAILURE);
	}*/
	ft_printf("Vamos a ejecutar el comando %s\n", cmd1);
	if (execve(cmd1, str_split1, NULL) == -1)
	{
		//perror("Error al ejecutar el comando1");
		//fprintf(stderr, "Esta entrando en 1");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	return (1);
}

/*Funcion hijo que lee del pipe entre comandos y escribe en el file2*/
int	pipe_file(int fd_out, int fd_pipe[2], char **argv, char **envp)
{
	char	**str_split2;
	char	*cmd2;

	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	str_split2 = ft_split(argv[3], ' ');
	if (str_split2 == NULL)
	{
		//perror("Error al hacer split");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	cmd2 = get_cmd_path(str_split2[0], envp);
	/*if (cmd2 == NULL)
	{
		perror("Error al reservar memoria");
		exit(EXIT_FAILURE);
	}*/
	//ft_printf("Vamos a ejecutar el comando %s %s\n", str_split2[0], str_split2[1]);
	if (execve(cmd2, str_split2, NULL) == -1)
	{
		//perror("Error al ejecutar el comando2");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	return (1);
}

/*Funcion padre*/
int	parent(int fd_in, int fd_out, int fd_pipe[2], char **argv, char **envp)
{
	pid_t	pid_out;

	close(fd_pipe[1]);
	close(fd_in);
	pid_out = fork();
	if (pid_out == -1)
	{
		//perror("Error al hacer el fork()");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	//fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pid_out == 0)
		pipe_file(fd_out, fd_pipe, argv, envp);
	else
	{
		close(fd_pipe[0]);
		waitpid(pid_out, NULL, 0);
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
	pid_t	pid_in;

	if (pipe(fd_pipe) == -1)
	{
		//perror("Error");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_in == -1 || fd_out == -1)
	{
		//perror("Error al abrir files");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	pid_in = fork();
	if (pid_in == -1)
	{
		//perror("Error al hacer el fork");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	if (pid_in == 0)
		file_pipe(fd_in, fd_pipe, argv, envp);
	else
	{
		parent(fd_in, fd_out, fd_pipe, argv, envp);
		waitpid(pid_in, NULL, 0);
		close(fd_in);
		close(fd_out);
	}
	return (1);
}

/*Programa main principal*/
int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		//perror("Error");
		ft_print_error();
		exit(EXIT_FAILURE);
	}
	if (ft_pipex(argv, envp) == 1)
		exit(EXIT_SUCCESS);
	return (0);
}
