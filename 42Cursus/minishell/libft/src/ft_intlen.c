/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:59:56 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/18 14:17:51 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "libft.h"
#include <stdio.h>
*/
int	ft_intlen(int n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}
/*
int	main(int argc, char *argv[])
{
	int	num;
	int	len;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	num = ft_atoi(argv[1]);
	len = ft_intlen(num);
	printf("El numero tiene %d digitos.\n", len);
	return (0);
}
*/
