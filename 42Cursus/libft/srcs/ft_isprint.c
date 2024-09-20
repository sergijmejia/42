/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:48:42 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/20 14:53:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libft.h"*/

int	ft_isprint(int c)
{
	if ((c >= 32) && (c <= 126))
		return (1);
	return (0);
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	if (ft_strlen(argv[1]) > 1)
	{
		printf("Cantidad de caracteres incorrecta\n");
		return (1);
	}
	if (ft_isascii(*argv[1]))
		printf("la funcion ft_isprint dice que SI es un caracter imprimible\n");
	else
		printf("la funcion ft_isprint dice que NO es un caracter imprimible\n");
	if (isascii(*argv[1]))
		printf("la funcion isprint dice que SI es un caracter imprimible\n");
	else
		printf("la funcion isprint dice que NO es un caracter imprimible\n");
	return (0);
}
*/
