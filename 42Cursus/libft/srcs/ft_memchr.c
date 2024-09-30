/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:37:26 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/30 19:03:42 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (s == NULL)
		return (NULL);
	c = (unsigned char) c;
	str = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (str[i] == c)
		{
			return ((void *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(int argc, char *argv[])
{
	unsigned char	*src;
	unsigned char	*src_ft;
	//char	*src_null;
	size_t			num;
	int				value;

	if (argc != 4)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	//src_null = NULL;
	value = atoi(argv[2]);
	num = (size_t) atoi(argv[3]);
	src = memchr(argv[1], value, num);
	src_ft = ft_memchr(argv[1], value, num);
	printf("El byte buscado es %c\n", value);
	if (src == NULL)
		printf("memchr no encontro el byte %d\n", value);
	else
		printf("El string desde mem, es: %s\n", src);
	if (src_ft == NULL)
		printf("ft_memchr no encontro el byte %d\n", value);
	else
		printf("El string desde ft_strchr es: %s\n", src_ft);
	return (0);
}
*/
