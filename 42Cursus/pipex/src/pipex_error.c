/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:06:17 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/04 17:01:01 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Funcion que imprime el error*/
void	print_error(char *str, int exit_code)
{
	char	*str_error_to_print;
	int		len;
	int		saved_errno;

	saved_errno = errno;
	str_error_to_print = ft_strjoin(str, "\n");
	free(str);
	if (str_error_to_print == NULL)
	{
		errno = saved_errno;
		exit(exit_code);
	}
	len = (int) ft_strlen(str_error_to_print);
	if (write(2, str_error_to_print, len) == -1)
		errno = saved_errno;
	free(str_error_to_print);
	exit(exit_code);
}

/*Funcion para mostrar por el canal correspondiente los mensajes de error
internos*/
void	ft_print_error(void)
{
	char	*str_error;
	char	*str_error_to_print;
	int		len;
	int		saved_errno;

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
