/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:58:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/06 13:54:13 by smejia-a         ###   ########.fr       */
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

/*Funcion para construir la ruta del comando*/
static char	*build_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*tmp_path;
	char	*cmd_path;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp_path = ft_strjoin(paths[i], "/");
		if (tmp_path == NULL)
			return (NULL);
		cmd_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

/*Funcion para obtener la ruta del comando*/
static char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	cmd_path = build_cmd_path(cmd, paths);
	ft_clean_split(paths);
	return (cmd_path);
}

/*Funcion que maneja el error de execve*/
static void	execve_error(char **cmd_args)
{
	int	exit_code;

	if (errno == EACCES)
	{
		exit_code = ft_print_command_error(cmd_args[0]);
		ft_clean_split(cmd_args);
		exit(exit_code);
	}
	else
	{
		ft_clean_split(cmd_args);
		ft_print_error();
	}
}

/*Funcion que maneja la ejecucion del comando*/
static void	execute_command(char **cmd_args, char **envp)
{
	char	*cmd;
	int		exit_code;

	cmd = get_cmd_path(cmd_args[0], envp);
	if (cmd == NULL)
	{
		errno = ENOENT;
		exit_code = ft_print_command_error(cmd_args[0]);
		ft_clean_split(cmd_args);
		exit(exit_code);
	}
	if (execve(cmd, cmd_args, NULL) == -1)
	{
		free(cmd);
		execve_error(cmd_args);
	}
}

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
static int	internal_child(t_arguments arg, int i, int fd_pipe_in)
{
	pid_t	pid_cmd;
	int		fd_pipe_out[2];
	int		status;
	int		exit_code;
	
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
		waitpid(pid_cmd, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			exit(exit_code);
		close(fd_pipe_out[1]);
	}
	return (fd_pipe_out[0]);
}

/*Funcion padre*/
static void	parent(int fd_file[2], int fd_pipe[2], t_arguments arg)
{
	pid_t	pid_out;
	int		i;
	int		status;
	int		exit_code;
	int		fd_pipe_in;

	if (fd_file[0] != -1)
		close(fd_file[0]);
	close(fd_pipe[1]);
	fd_pipe_in = fd_pipe[0];
	i = 0;
	while (i < (arg.argc - 5))
	{
		fd_pipe_in = internal_child(arg, i, fd_pipe_in);
		i++;
	}
	pid_out = fork();
	if (pid_out == -1)
		ft_print_error();
	if (pid_out == 0)
		pipe_file(fd_file[1], fd_pipe_in, arg);
	else
	{
		close(fd_pipe_in);
		waitpid(pid_out, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			exit(exit_code);
		close(fd_file[1]);
	}
}

/*Funcion que maneja el proceso hijo*/
static void	first_child(int fd, int pipe[2], int saved_errno, t_arguments arg)
{
	if (fd == -1)
		exit(ft_print_file_error(arg.argv[1], saved_errno));
	file_pipe(fd, pipe, arg);
}

/*Funcion pipex*/
static int	ft_pipex(t_arguments arg, int fd_file[2], int saved_errno[2])
{
	int		fd_pipe[2];
	int		status;
	pid_t	pid_in;
	char	*exit_file;

	if (pipe(fd_pipe) == -1)
		ft_print_error();
	pid_in = fork();
	if (pid_in == -1)
		ft_print_error();
	if (pid_in == 0)
		first_child(fd_file[0], fd_pipe, saved_errno[0], arg);
	else
	{
		exit_file = arg.argv[arg.argc - 1];
		if (fd_file[1] == -1)
			exit(ft_print_file_error(exit_file, saved_errno[1]));
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
	char	*exit_file;

	saved_errno[0] = 0;
	saved_errno[1] = 0;
	exit_file = arg.argv[arg.argc - 1];
	fd_file[0] = open(arg.argv[1], O_RDONLY);
	if (fd_file[0] == -1)
		saved_errno[0] = errno;
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
