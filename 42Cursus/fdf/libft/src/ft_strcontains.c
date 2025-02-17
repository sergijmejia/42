/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:17:50 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/03 17:09:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_strcontains(const char *str, char c)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}
/*
int	main(int argc, char *argv[])
{
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
	if (ft_strcontains(argv[1], *argv[2]))
		printf("Segun ft_strcontains SI esta en el string\n");
	else
		printf("Segun ft_strcontains NO esta en el string\n");
	return (0);
}
*/
