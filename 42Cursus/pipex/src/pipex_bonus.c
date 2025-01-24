/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:58:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/22 11:39:27 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Abrimos el archivo1*/

/*Definimos el proceso que lee del archivo1 -> esto no es asi porque el archivo1
lo lee el padre y psa la informacion directa al pipe*/
pid_t	file_pipe(int fd_pipe[2], int fd, char *str) //para el primer comando
{
	pid_t	pid;
	char	**str_split;
	char    *cmd;

	pid = fork();
	if (pid == -1)
	{
		perror("Error al crear hijo");
		return (-1);
	}
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	else
		close(fd_pipe[1]);
	str_split = ft_split(str, ' ');
	cmd = malloc (9 + ft_strlen(str_split[0]) + 1);
	ft_memcpy(cmd, "/usr/bin/", 9);
	ft_memcpy(cmd + 9, str_split[0], ft_strlen(str_split[0]));
	cmd[9 + ft_strlen(str_split[0])] = '\0';
	ft_printf("Vamos a ejecutar el comando %s\n", cmd);
	if (execve(cmd, str_split, NULL) == -1)
	{
		perror("Error al ejecutar el comando");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

pid_t	pipe_pipe(int fd_pipe_in[2], int fd_pipe_out[2], char *str) //para los comandos intermedios entre pipes
{
	pid_t	pid;
	char	**str_split;
	char	*cmd;

	pid = fork();
	if (pid == -1)
	{
		perror("Error al crear hijo");
		return (-1);
	}
	if (pid == 0)
	{
		dup2(fd_pipe_in[0], STDIN_FILENO);
		dup2(fd_pipe_out[1], STDOUT_FILENO);
		close(fd_pipe_in[0]);
		close(fd_pipe_in[1]);
		close(fd_pipe_out[0]);
		close(fd_pipe_out[1]);
	}
	str_split = ft_split(str, ' ');
	cmd = malloc (9 + ft_strlen(str_split[0]) + 1);
	ft_memcpy(cmd, "/usr/bin/", 9);
	ft_memcpy(cmd + 9, str_split[0], ft_strlen(str_split[0]));
	cmd[9 + ft_strlen(str_split[0])] = '\0';
	ft_printf("Vamos a ejecutar el comando %s\n", cmd);
	if (execve(cmd, str_split, NULL) == -1)
	{
		perror("Error al ejecutar el comando");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

pid_t	pipe_file(int fd_pipe[2], int fd, char *str)
{
	pid_t	pid;
	char	**str_split;
	char    *cmd;

	pid = fork();
	if (pid == -1)
	{
		perror("Error al crear hijo");
		return (-1);
	}
	if (pid == 0)
	{
		dup2(fd_pipe[1], STDIN_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	str_split = ft_split(str, ' ');
	cmd = malloc (9 + ft_strlen(str_split[0]) + 1);
	ft_memcpy(cmd, "/usr/bin/", 9);
	ft_memcpy(cmd + 9, str_split[0], ft_strlen(str_split[0]));
	cmd[9 + ft_strlen(str_split[0])] = '\0';
	ft_printf("Vamos a ejecutar el comando %s\n", cmd);
	if (execve(cmd, str_split, NULL) == -1)
	{
		perror("Error al ejecutar el comando");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

/*Definimos el  que es el comandon*/


/*Definimos el hijo_a2 que es el achivo2*/


/*Pipe que conecta el archivo1 con el comando1*/


/*Pipe que conecta dos comandos
static void	def_pipe(int fd_pipe[2], int fd)
{
	if (pipe(fd_pipe) == -1)
	}
		perror("Error al crear pipe");
		close(fd);
		exit(EXIT_FAILURE);
	}
}*/

/*Pipe que conecta el ultimo comando con el archivo2*/

/*Programa main principal*/
int	main(int argc, char **argv)
{
	int	fd_infile;
	int	fd_outfile;
	int	num_pipes;
	int	(*fd_pipe)[2]; //deben haber tantos fd como hijos
	int	i;
	pid_t	*pid;

	fd_infile = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile == -1 || fd_outfile == -1)
	{
		perror("Error al abrir archivos");
		exit(EXIT_FAILURE);
	}
	num_pipes = argc - 4;
	fd_pipe = (int (*)[2])malloc(sizeof(int[2])*num_pipes);
	if (!fd_pipe)
	{
		perror("Error al asignar memoria para los pipes"); //verificar este mensaje
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_pipes) //se definen todos los pipes que se vana utilizar
	{
		if (pipe(fd_pipe[i]) == -1)
		{
			perror("Error crear pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pid = (pid_t *) malloc (sizeof(pid_t) * (num_pipes + 1));
	i = 0;
	while (i <= num_pipes)
	{
		if (i == 0)
			pid[i] = file_pipe(fd_pipe[i], fd_infile, argv[i + 2]);
		else if (i == num_pipes)
			pid[i] = pipe_file(fd_pipe[i], fd_outfile, argv[i + 2]);
		else
			pid[i] = pipe_pipe(fd_pipe[i - 1], fd_pipe[i], argv[i + 2]);

		i++;
	}
	/*Para cada uno de los comandos tengo que aplicar la funcion split para poder llamar */
	i = 0;
	while (i <= num_pipes)
	{
		if (waitpid(pid[i], NULL, 0) == -1)
			perror("Error al esperar hijo");
	}
	free(fd_pipe);
	free(pid);
	return (1);
}

