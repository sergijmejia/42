/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:36:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/20 13:30:44 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Libera memoria donde apunta el puntero str*/
char     *free_str(char **str)
{
        free(*str);
        *str = NULL;
        return (*str);
}

/*Aumenta la capacidad del buffer y copia el contenido anterior*/
char	*realloc_buffer(char **str, size_t new_len)
{
	char	*new_str;
	size_t	i;
	size_t	len;

	len = ft_strlen(*str);
	new_str = (char *) malloc(new_len + 1);
	if (!new_str)
		return (free_str(str));
	i = 0;
	while (i < len)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = '\0';
	free_str(str);
	*str = new_str;
	return (*str);
}

/*Extrae la linea desde el string acumulado y ajusta el putero str*/
char	*extract_line(char **str)
{
	char	*str_tmp;
	char	*str_return;
	int		end_line;

	end_line = ft_check_newline(*str);
	if (end_line == -1)
	{
		str_return = ft_strdup(*str);
		free_str(str);
		return(str_return);
	}
	if (end_line == (int) (ft_strlen(*str) - 1))
		str_tmp = NULL;
	else
	{
		str_tmp = ft_strdup(*str + end_line + 1);
		if (!str_tmp)
			return (free_str(str));
	}
	str_return = (char *) malloc(end_line + 2);
	if (!str_return)
	{
		free_str(&str_tmp);
		return (free_str(str));
	}
	ft_memcpy(str_return, *str, end_line + 1);
	str_return[end_line + 1] = '\0';
	free_str(str);
	*str = str_tmp;
	return (str_return);
}

/*Lee desde e archivo y agrega el contenido a str*/
int	read_to_buffer(int fd, char **str)
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
	int			str_null;
	int			readed;

	str_null = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str == NULL)
	{
		str_null = 1;
		str = (char *) malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	while (ft_check_newline(str) == -1)
	{
		readed = read_to_buffer(fd, &str);
		if (readed < 0 || (readed == 0 && str_null == 1))
			return (free_str(&str));
		if (readed == 0)
			return(extract_line(&str));
		str_null = 0;
	}
	return (extract_line(&str));
}
