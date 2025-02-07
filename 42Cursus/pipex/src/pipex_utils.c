/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:06:52 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/07 12:36:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

/*Funcion para construir la ruta del comando*/
char	*build_cmd_path(char *cmd, char **paths)
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
char	*get_cmd_path(char *cmd, char **envp)
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
void	execve_error(char **cmd_args)
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
void	execute_command(char **cmd_args, char **envp)
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
	if (execve(cmd, cmd_args, envp) == -1)
	{
		free(cmd);
		execve_error(cmd_args);
	}
}
