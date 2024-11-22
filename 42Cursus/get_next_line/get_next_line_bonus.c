/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:36:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/22 12:14:31 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*Aumenta la capacidad del buffer y copia el contenido anterior*/
static char	*realloc_buffer(char **str, size_t new_len)
{
	char	*new_str;
	size_t	i;
	size_t	len;

	len = ft_strlen(*str);
	new_str = (char *) malloc(new_len + 1);
	if (!new_str)
		return (ft_free_str(str));
	i = 0;
	while (i < len)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = '\0';
	ft_free_str(str);
	*str = new_str;
	return (*str);
}

/*Crea el str_return para el extract_line*/
static char	*create_str_return(char **str, int end_line, char **str_tmp)
{
	char	*str_return;

	str_return = (char *) malloc(end_line + 2);
	if (!str_return)
	{
		ft_free_str(str_tmp);
		return (ft_free_str(str));
	}
	ft_memcpy(str_return, *str, end_line + 1);
	str_return[end_line + 1] = '\0';
	ft_free_str(str);
	*str = *str_tmp;
	return (str_return);
}

/*Extrae la linea desde el string acumulado y ajusta el putero str*/
static char	*extract_line(char **str)
{
	char	*str_tmp;
	char	*str_return;
	int		end_line;

	end_line = ft_check_newline(*str);
	if (end_line == -1)
	{
		str_return = ft_strdup(*str);
		ft_free_str(str);
		return (str_return);
	}
	if (end_line == (int)(ft_strlen(*str) - 1))
		str_tmp = NULL;
	else
	{
		str_tmp = ft_strdup(*str + end_line + 1);
		if (!str_tmp)
			return (ft_free_str(str));
	}
	return (create_str_return(str, end_line, &str_tmp));
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
	static char	*str[OPEN_MAX];
	int			str_null;
	int			readed;

	str_null = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str[fd] == NULL)
	{
		str_null = 1;
		str[fd] = (char *) malloc(1);
		if (!str[fd])
			return (NULL);
		str[fd][0] = '\0';
	}
	while (ft_check_newline(str[fd]) == -1)
	{
		readed = read_to_buffer(fd, &str[fd]);
		if (readed < 0 || (readed == 0 && str_null == 1))
			return (ft_free_str(&str[fd]));
		if (readed == 0)
			return (extract_line(&str[fd]));
		str_null = 0;
	}
	return (extract_line(&str[fd]));
}
