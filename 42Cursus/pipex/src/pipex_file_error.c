/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_file_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:16 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/04 18:24:46 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion para imprimir los errores de archivos no encontrados*/
static void	file_not_found_error(char *file)
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
		exit(exit_code);
	}
	print_error(str_error, exit_code);
}

/*Funcion para imprimir los errores de comandos o archivos sin permisos*/
static void	permission_file_denied_error(char *file)
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
archivos*/
void	ft_print_file_error(char *file, int saved_errno)
{
	errno = saved_errno;
	if (errno == 2)
		file_not_found_error(file);
	else if (errno == 13)
		permission_file_denied_error(file);
	else if (errno == 21)
		is_directory_error(file);
	else
		exit(EXIT_FAILURE);
}
