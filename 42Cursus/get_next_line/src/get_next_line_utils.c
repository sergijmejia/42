/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:34:22 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/11 13:46:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check_end_line(const char *str, size_t len)
{
	size_t	i;
	size_t	len;
	
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	len = ft_strlcpy(str, s, len + 1);
	return (str);
}

size_t	ft_strlen(char *str)
{
	size_t	l;

	l = 0;
	while (*str != '\0')
	{
		l++;
		str++;
	}
	return (l);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*aux_dest;
	unsigned char	*aux_src;
	size_t			i;

	if (n == 0 || (dest == NULL && src == NULL))
		return (dest);
	aux_dest = (unsigned char *) dest;
	aux_src = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		aux_dest[i] = aux_src[i];
		i++;
	}
	return (dest);
}

