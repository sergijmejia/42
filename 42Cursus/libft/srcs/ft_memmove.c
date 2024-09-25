/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:26:10 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/25 17:21:56 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
/*#include <string.h>
#include <stdio.h>
#include <stdlib.h>*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*aux;

	if ((dest == NULL) || (src == NULL))
		return (NULL);
	aux = (unsigned char *) dest;
	aux = ft_memcpy(aux, src, n);
	dest = ft_memcpy(dest, aux, n);
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
	new_strft = ft_memmove(new_strft, argv[1], 5);
	new_str = memmove(new_str, argv[1], 5);
	printf("El nuevo string con la funcion ft es %s\n", new_strft);
	printf("El nuevo string con la cuncion m es %s\n", new_str);
	return (0);
}*/
