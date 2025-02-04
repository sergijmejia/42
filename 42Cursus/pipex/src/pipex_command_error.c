/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_command_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:11:57 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/04 16:39:37 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion para imprimir los errores de comandos no encontrados*/
static void	command_not_found_error(char *cmd)
{
	char	*str_error;
	int		saved_errno;
	int		exit_code;

	saved_errno = errno;
	exit_code = 127;
	str_error = ft_strjoin("command not found: ", cmd);
	if (str_error == NULL)
	{
		errno = saved_errno;
		exit(exit_code);
	}
	print_error(str_error, exit_code);
}

/*Funcion para imprimir los errores de comandos sin permisos*/
static void	permission_command_denied_error(char *cmd)
{
	char	*str_error;
	int		saved_errno;
	int		exit_code;

	saved_errno = errno;
	exit_code = 126;
	str_error = ft_strjoin("permission denied: ", cmd);
	free(cmd);
	if (str_error == NULL)
	{
		errno = saved_errno;
		exit(exit_code);
	}
	print_error(str_error, exit_code);
}

/*Funcion para mostrar por su canal correspondiente los mensajes de error de
comandos*/
void	ft_print_command_error(char *cmd)
{
	if (errno == 2)
		command_not_found_error(cmd);
	else if (errno == 13)
		permission_command_denied_error(cmd);
	else
		exit(EXIT_FAILURE);
}
