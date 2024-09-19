/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:09:43 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/19 12:15:12 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>*/
#include "libft.h"

int	ft_isalpha(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
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
	if (ft_isalpha(*argv[1]))
		printf("la funcion ft_isalpha dice que SI es una letra\n");
	else
		printf("la funcion ft_isalpha dice que NO es una letra\n");
	if (isalpha(*argv[1]))
		printf("la funcion isalpha dice que SI es una letra\n");
	else
		printf("la funcion isalpha dice que NO es una letra\n");
	return (0);
}
*/