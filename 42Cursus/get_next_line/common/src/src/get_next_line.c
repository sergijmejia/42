/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:36:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/20 15:50:37 by smejia-a         ###   ########.fr       */
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

/*Funcion principal. Devuelve la siguiente linea de un archivo fd*/
char	*get_next_line(int fd)
{
	static char	*str;
	size_t		len;
	char    buffer[BUFFER_SIZE + 1];
	ssize_t		readed_char;
	int			readed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_check_newline(str) == -1)
	{
		readed_char = read(fd, buffer, BUFFER_SIZE);
		if (readed_char == -1)
			return (free_str(&str));
		else if (readed_char == 0)
			return(extract_line(&str));
		else
			str = ftstrjoin(str, buffer, len + readed_char + 1);
	}
	return (extract_line(&str));
}
