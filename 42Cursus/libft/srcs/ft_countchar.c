/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:53:32 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/03 16:14:05 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_countchar(const char *s, char c)
{
	int	i;
	int	aux;
	
	if (s == NULL)
		return (0);
	i = 0;
	aux = 0;
	while (s[i])
	{
		if (s[i] == c)
			aux++;
		i++;
	}
	return (aux);
}
/*
int	main(int argc, char *argv[])
{
	int	num;

	if (argc != 3)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	if (ft_strlen(argv[2]) > 1)
	{
		printf("Cantidad de caracteres incorrecta\n");
		return (1);
	}
	num = ft_countchar(argv[1], *argv[2]);
	printf("Segun ft_countchar %c se puede encontrar %d veces en %s\n", *argv[2], num, argv[1]);
	return (0);
}
*/
