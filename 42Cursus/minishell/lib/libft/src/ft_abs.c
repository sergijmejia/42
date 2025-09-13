/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:12:44 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/04 17:20:33 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_abs(int num)
{
	if (num == INT_MIN)
		return (num);
	if (num < 0)
		num = (-1) * num;
	return (num);
}
/*
int	main(int argc, char *argv[])
{
	int	num;
	int	abs;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	num = ft_atoi(argv[1]);
	abs = ft_abs(num);
	printf("El valor absoluto es: %d\n", abs);
	return (0);
}
*/
