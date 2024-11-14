/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:36:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/14 12:07:46 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Aumenta la capacidad del buffer y copia el contenido anterior*/
static char	*realloc_buffer(char **str, size_t new_len)
{
	char	*new_str;
	size_t	i;
	size_t	len;

	len = ft_strlen(*str);
	new_str = (char *) malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = '\0';
	free(*str);
	*str = new_str;
	return (*str);
}

/*Extrae la linea desde el string acumulado y ajusta el putero str*/
static char	*extract_line(char **str)
{
	char	*str_tmp;
	char	*str_return;
	size_t	len;
	int		end_line;

	len = ft_strlen(*str);
	end_line = ft_check_newline(*str);
	str_tmp = ft_strdup(*str + end_line + 1);
	if (!str_tmp)
		return (NULL);
	str_return = (char *) malloc(end_line + 2);
	if (!str_return)
		return (NULL);
	ft_memcpy(str_return, *str, end_line + 1);
	str_return[end_line + 1] = '\0';
	free(*str);
	*str = str_tmp;
	return (str_return);
}

/*Lee desde e archivo y agrega el contenido a str*/
static int	read_to_buffer(int fd, char **str)
{
	ssize_t	readed_char;
	char	buffer[BUFFER_SIZE + 1];
	size_t	len;
	int		i;

	len = ft_strlen(*str);
	readed_char = read(fd, buffer, BUFFER_SIZE);
	if (readed_char == -1)
		return (-1);
	if (readed_char == 0)
		return (0);
	if (realloc_buffer(str, len + readed_char) == NULL)
		return (-1);
	i = 0;
	while (i < readed_char)
	{
		(*str)[len + i] = buffer[i];
		i++;
	}
	(*str)[len + readed_char] = '\0';
	return (1);
}

/*Funcion principal. Devuelve la siguiente linea de un archivo fd*/
char	*get_next_line(int fd)
{
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str == NULL)
	{
		str = (char *) malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	while (ft_check_newline(str) == -1)
	{
		if (read_to_buffer(fd, &str) <= 0)
		{
			free(str);
			str = NULL;
			return (NULL);
		}
	}
	return (extract_line(&str));
}
