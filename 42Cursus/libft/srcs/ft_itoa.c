/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:03:11 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/04 17:22:21 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		num;

	len = ft_intlen(n);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	num = ft_abs(n);
	if (num == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", (size_t)(len + 1));
		return (str);
	}
	while (len > 1)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	else
		str[0] = num + '0';
	return (str);
}
/*
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
	str = ft_itoa(num);
	printf("El numero recibido con ft es %s\n", str);
	return (0);
}
*/
