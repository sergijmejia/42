/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:03:47 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/26 15:46:30 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libft.h"
*/
int	ft_isascii(int c)
{
	if ((c >= 0) && (c <= 127))
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
		printf("la funcion ft_isascii dice que SI es un caracter ascii\n");
	else
		printf("la funcion ft_isascii dice que NO es un caracter ascii\n");
	if (isascii(*argv[1]))
		printf("la funcion isascii dice que SI es un caracter ascii\n");
	else
		printf("la funcion isascii dice que NO es un caracter ascii\n");
	return (0);
}
*/
