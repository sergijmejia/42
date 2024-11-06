/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:03:11 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/18 14:17:25 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		num;

	len = ft_intlen(n, 10);
	str = ft_calloc((size_t)(len + 1), 1);
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
