/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:26:10 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/26 19:15:41 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
/*#include <string.h>
#include <stdio.h>
#include <stdlib.h>*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if ((dest == NULL) || (src == NULL))
		return (NULL);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (d < s)
		d = ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
/*
int	main(int argc, char *argv[])
{
	char	*new_str;
	char	*new_strft;
	char	*argv_cpy;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	argv_cpy = (char *) malloc (ft_strlen(argv[1]) * sizeof(char));
	argv_cpy = ft_memcpy(argv_cpy, argv[1], ft_strlen(argv[1]));
	new_strft = &argv_cpy[8];
	new_strft = ft_memmove(new_strft, argv_cpy, 10);
	new_str = &argv[1][8];
	new_str = memmove(new_str, argv[1], 10);
	printf("El nuevo string con la funcion ft es %s\n", new_strft);
	printf("El nuevo string con la cuncion m es %s\n", new_str);
	free(arg_cpy);
	return (0);
}*/
