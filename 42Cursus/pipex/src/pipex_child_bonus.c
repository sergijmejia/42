/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:53:13 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/07 19:54:20 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion hijo que lee el file1 y escribe en el pipe entre los comandos*/
static void	file_pipe(int fd_in, int fd_pipe[2], t_arguments arg)
{
	char	**cmd_args;
	char	*cmd;

	close(fd_pipe[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_print_error();
	close(fd_in);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		ft_print_error();
	close(fd_pipe[1]);
	if (ft_strncmp(arg.argv[1], "here_doc", 8) == 0)
		cmd = arg.argv[3];
	else
		cmd = arg.argv[2];
	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		ft_print_error();
	execute_command(cmd_args, arg.envp);
}

/*Funcion que maneja el proceso hijo*/
void	first_child(int fd, int pipe[2], int saved_errno, t_arguments arg)
{
	if (fd == -1)
	{
		if (ft_strncmp(arg.argv[1], "here_doc", 8) == 0)
			exit(ft_print_file_error(".tmp_pipex", saved_errno));
		else
			exit(ft_print_file_error(arg.argv[1], saved_errno));
	}
	file_pipe(fd, pipe, arg);
}
