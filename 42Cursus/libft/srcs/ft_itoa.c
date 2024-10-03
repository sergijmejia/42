/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:03:11 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/03 18:06:40 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		aux;
	int		num;

	len = 0;
	aux = n;
	if (n < 0)
		len++;
	while (aux != 0)
	{
		aux = aux / 10;
		len++;
	}
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	num = n;
	while (len > 1)
	{
		aux = n % 10;
		if (aux < 0)
			aux = aux * (-1);
		str[len - 1] = aux + '0';
		n = n / 10;
		len--;
	}
	if (num < 0)
		str[0] = '-';
	else
		str[0] = n + '0';
	return (str);
}

int	main(int argc, char *argv[])
{
	int		num;
	char	*str;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	num = ft_atoi(argv[1]);
	str = ft_atoi(num);
	printf("El numero recibido con ft es %s\n", str);
	return (0);
}
