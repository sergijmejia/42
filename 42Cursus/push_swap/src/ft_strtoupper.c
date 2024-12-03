/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:33:24 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/09 10:46:21 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_strtoupper(void *str)
{
	char	*aux;

	if (str == NULL)
		return ;
	aux = (char *)str;
	while (*aux)
	{
		*aux = ft_toupper(*aux);
		aux++;
	}
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	printf("El texto original es: %s\n", argv[1]);
	ft_strtoupper(argv[1]);
	printf("El texto despues de ft_strtoupper es: %s\n", argv[1]);
	return (0);
}
*/
