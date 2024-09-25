/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:59:25 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/25 13:22:38 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/*#include <stdio.h>
#include <string.h>
#include "libft.h"*/

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*aux;
	size_t			i;

	if (ptr == NULL)
		return (NULL);
	if (num == 1)
		return (ptr);
	aux = (unsigned char *) ptr;
	i = 1;
	while (i < num)
	{
		*aux = (unsigned char) value;
		aux++;
		i++;
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