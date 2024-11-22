/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:34:22 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/22 12:22:11 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*Libera memoria donde apunta el puntero str*/
char	*ft_free_str(char **str)
{
	free(*str);
	*str = NULL;
	return (*str);
}

/*Busca la posicion del caracter '\n' en str*/
int	ft_check_newline(char *str)
{
	int		i;
	char	c;

	if (!str)
		return (-1);
	i = 0;
	while (str && str[i] != '\0')
	{
		c = str[i];
		if (c == '\n')
			return (i);
		i++;
	}
	return (-1);
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

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen((char *) s);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, len + 1);
	return (str);
}
