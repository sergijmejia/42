/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:59:25 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/20 15:00:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
/*#include <stdio.h>
#include "libft.h"*/

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*aux;

	aux = (unsigned char *) ptr;
	while (num > 1)
	{
		*aux = (unsigned char) value;
		aux++;
		num--;
	}
	*aux = (unsigned char) value;
	return (ptr);
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
	new_strft = ft_memset(argv[1], 'A', ft_strlen(argv[1]));
	new_str = memset(argv[1], 'A', ft_strlen(argv[1]));
	printf("El nuevo string con la funcion ft es %s\n", new_strft);
	printf("El nuevo string con la cuncion m es %s\n", new_str);
	return (0);
}
*/
