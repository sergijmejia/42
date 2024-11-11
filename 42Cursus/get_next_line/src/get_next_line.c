/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:35:29 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/11 13:46:00 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	ssize_t	readed_char;
	static char	*str;
	char	*str_tmp;
	char		*str_return;
	char	buffer[BUFFER_SIZE];
	size_t		len;
	int			end_line;

	if (!str)
	{
		len = 0;
		str = (char *) malloc (BUFFER_SIZE + 1);
	}
	else
	{
		len = ft_strlen(str);
		end_line = ft_check_end_line(str, len);
		if (end_line != -1)
		{
			str_tmp = ft_strdup(&str[end_line + 1]);
			if (!str_tmp)
			{
				free(str);
				return (NULL);
			}
			str_return = (char *) malloc (end_line + 2);
			if (!str_return)
			{
				free(str_tmp);
				free(str);
				return (NULL);
			}
			ft_memcpy(str_return, str, end_line + 1);
			str_return[end_line + 1] = '\0';
			free(str);
			str = str_tmp;
			return (str_return);
		}
		str_tmp = (char *) malloc (len + BUFFER_SIZE + 1);
		if (!str_tmp)
		{
			free(str);
			return (NULL);
		}
		ft_memcpy(str_tmp, str, len);
		free (str);
		str = str_tmp;

	}
	readed_char = read(fd, buffer, BUFFER_SIZE);
	if (readed_char == -1 || (readed_char == 0 && len == 0))
	{
		free(str);
		return (NULL);
	}
	if (readed_char == 0) 
		get_next_line(fd);
	ft_memcpy(&str[len], buffer, (size_t) readed_char);
	str[len + readed_char] = '\0';
	get_next_line(fd);	
}
