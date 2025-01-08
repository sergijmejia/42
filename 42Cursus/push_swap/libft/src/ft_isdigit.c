/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:00:48 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/26 15:46:59 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libft.h"
*/
int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
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
	if (ft_isdigit(*argv[1]))
		printf("la funcion ft_isdigit dice que SI es un digito\n");
	else
		printf("la funcion ft_isdigit dice que NO es un digito\n");
	if (isdigit(*argv[1]))
		printf("la funcion isdigit dice que SI es un digito\n");
	else
		printf("la funcion isdigit dice que NO es un digito\n");
	return (0);
}
*/
