/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_file_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:16 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/05 12:13:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion para imprimir los errores de archivos no encontrados*/
static int	file_not_found_error(char *file)
{
	char	*str_error;
	int		saved_errno;
	int		exit_code;

	saved_errno = errno;
	exit_code = 127;
	str_error = ft_strjoin("not such file or directory: ", file);
	if (str_error == NULL)
	{
		errno = saved_errno;
		return (exit_code);
	}
	print_error(str_error);
	return (exit_code);
}

/*Funcion para imprimir los errores de comandos o archivos sin permisos*/
static int	permission_file_denied_error(char *file)
{
	char	*str_error;
	int		saved_errno;
	int		exit_code;

	saved_errno = errno;
	exit_code = 126;
	str_error = ft_strjoin("permission denied: ", file);
	if (str_error == NULL)
	{
		errno = saved_errno;
		return (exit_code);
	}
	print_error(str_error);
	return (exit_code);
}

/*Funcion para imprimir los errores de archivos cuando el nombre corresponde a
una carpeta*/
static int	is_directory_error(char *file)
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
		return (exit_code);
	}
	print_error(str_error);
	return (exit_code);
}

/*Funcion para mostrar por su canal correspondiente los mensajes de error de
archivos*/
int	ft_print_file_error(char *file, int saved_errno)
{
	errno = saved_errno;
	if (errno == 2)
		return (file_not_found_error(file));
	else if (errno == 13)
		return (permission_file_denied_error(file));
	else if (errno == 21)
		return (is_directory_error(file));
	else
		return (EXIT_FAILURE);
}
