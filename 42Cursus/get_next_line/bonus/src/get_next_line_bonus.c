/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:36:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/14 16:32:11 by smejia-a         ###   ########.fr       */
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

/*Devuelve la siguiente linea de un archivo fd especifico*/
char	*get_next_line_fd(int fd, char **str)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (*str == NULL)
	{
		*str = (char *) malloc(1);
		if (!*str)
			return (NULL);
		*str[0] = '\0';
	}
	while (ft_check_newline(*str) == -1)
	{
		if (read_to_buffer(fd, str) <= 0)
		{
			free(*str);
			*str = NULL;
			return (NULL);
		}
	}
	return (extract_line(str));
}

typedef struct s_file 
{
	int		fd;
	char	*str;
} fd_file;

char	*get_next_line(int fd)
{
	static fd_file	*files;
	fd_file	*files_tmp;
	size_t	i;
	size_t	j;
	size_t	len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (files == NULL)
	{
                files = malloc (2 * sizeof(fd_file));
                if (!files)
                        return (NULL);
		files[0].fd = fd;
                files[0].str = NULL;
		files[1].fd = -2;
		files[1].str = NULL;
        }
	i = 0;
	while (files[i].fd != -2)
	{
		if (files[i].fd == fd)
			return (get_next_line_fd(files[i].fd, &files[i].str));
		i++;
	}
	files_tmp = malloc ((i + 2) * sizeof(fd_file));
	if (!files_tmp)
	{
		while (i > 0)
		{
			free(files[i - 1].str);
			i--;
		}
		free(files);
		return (NULL);
	}
	files_tmp[0].fd = fd;
	files_tmp[0].str = NULL;
	files_tmp[i + 1].fd = -2;
	files_tmp[i + 1].str = NULL;
	j = i - 1;
	while (i > 0)
	{
		len = ft_strlen(files[i - 1].str);
		files_tmp[i].fd = files[i - 1].fd;
		files_tmp[i].str = (char *) malloc (len + 1);
		if (!files_tmp[i].str)
		{
			while (i < j + 1)
			{
				free(files_tmp[i + 1].str);
				i++;
			}
			free(files_tmp);
			while (j >= 0)
			{
				free(files[j].str);
				j--;
			}
			free(files);
			return (NULL);
		}
		ft_memcpy(files_tmp[i].str, files[i - 1].str, len + 1);
		i--;
	}
	while (j >= 0)
	{
		free(files[j].str);
		j--;
	}
	free(files);
	files = files_tmp;
	return (get_next_line_fd(files[0].fd, &files[0].str));
}
