/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:20:52 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/06 02:52:20 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include "libft.h"
*/
int	ft_tolower(int c)
{
	if ((c >= 'A') && (c <= 'Z'))
		c = c + ('a' - 'A');
	return (c);
}
/*
int	main(int argc, char *argv[])
{
	char	c;

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
	printf("El caracter orignal es: %s\n", argv[1]);
	c = ft_tolower(*argv[1]);
	printf("El caracter despues de ft_lower es: %c\n", c);
	return (0);
}
*/
