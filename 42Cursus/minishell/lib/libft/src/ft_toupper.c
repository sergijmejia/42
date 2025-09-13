/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:59:32 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/27 18:20:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include "libft.h"
*/
int	ft_toupper(int c)
{
	if ((c >= 97) && (c <= 122))
		c = c - ('a' - 'A');
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
	c = ft_toupper(*argv[1]);
	printf("El caracter despues de ft_toupper es: %c\n", c);
	return (0);
}
*/
