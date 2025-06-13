/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:08:39 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/18 14:18:55 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		len;
	int		num;

	len = ft_intlen(n, 10);
	num = ft_abs(n);
	if (num == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", 12);
		ft_putstr_fd(str, fd);
		return ;
	}
	str[len] = '\0';
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
	ft_putstr_fd(str, fd);
}
/*
int	main(int argc, char *argv[])
{
	int	num;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	num = ft_atoi(argv[1]);
	ft_putnbr_fd(num, 1);
	return (0);
}
*/
