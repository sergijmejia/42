/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:20:27 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/10 16:20:43 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/*#include <stdio.h>
#include <string.h>
#include "libft.h"
#include <stdlib.h>*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*aux_dest;
	unsigned char	*aux_src;
	size_t			i;

	if ((dest == NULL) || (src == NULL))
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
/*
int	main(int argc, char *argv[])
{
	char	*new_str;
	char	*new_strft;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	new_strft = (char *) malloc (ft_strlen(argv[1]) * sizeof(char));
	new_str = (char *) malloc (ft_strlen(argv[1]) * sizeof(char));
	new_strft = ft_memcpy(new_strft, argv[1], 5);
	new_str = memcpy(new_str, argv[1], 5);
	printf("El nuevo string con la funcion ft es %s\n", new_strft);
	printf("El nuevo string con la cuncion m es %s\n", new_str);
	free(new_str);
	free(new_strft);
	return (0);
}*/
