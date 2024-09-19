/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:26:36 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/19 13:46:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>*/
#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
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
	if (ft_isalnum(*argv[1]))
		printf("la funcion ft_isalnum dice que SI es un digito\n");
	else
		printf("la funcion ft_isalnum dice que NO es un digito\n");
	if (isalnum(*argv[1]))
		printf("la funcion isalnum dice que SI es un digito\n");
	else
		printf("la funcion isalnum dice que NO es un digito\n");
	return (0);
}
*/
