/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:06:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/26 19:17:25 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
/*#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	n;

	n = ft_strlen(src);
	if (n >= (size - 1))
	{
		dest = ft_memcpy(dest, src, (size - 1));
		dest[size - 1] = '\0';
	}
	else
	{
		dest = ft_memcpy(dest, src, n);
		dest[n] = '\0';
	}
	return (n + 1);
}
/*
int	main(int argc, char *argv[])
{
	//char	*new_str;
	char	*new_strft;
	//int		n;
	int		n_ft;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	new_strft = (char *) malloc (10 * sizeof(char));
	//new_str = (char *) malloc (10 * sizeof(char));
	n_ft = (int)ft_strlcpy(new_strft, argv[1], 40);
	//n = (int)strlcpy(new_str, argv[1], 40);
	printf("El nuevo string con la funcion ft es %s\n", new_strft);
	printf("La longitud de la frase original medida con ft es  %d\n", n_ft);
	//printf("El nuevo string con la cuncion s es %s\n", new_str);
	//printf("La longitud de la frase original medida con s es  %d\n", n);
	free(new_strft);
	//free(new_str);
	return (0);
}*/
