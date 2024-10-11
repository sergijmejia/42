/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:17:47 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/11 15:51:53 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>
*/
int	ft_atoi(const char *nptr)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*nptr && ((*nptr >= '\t' && *nptr <= '\r') || (*nptr == ' ')))
		nptr++;
	if (*nptr == '-')
		negative = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	return (res * negative);
}
/*
int	main(int argc, char *argv[])
{
	int	num_ft;
	int	num;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	num_ft = ft_atoi(argv[1]);
	printf("El numero recibido con ft es %d\n", num_ft);
	num = atoi(argv[1]);
	printf("El numero recibido es %d\n", num);
	return (0);
}
*/
