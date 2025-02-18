/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:50:54 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:45:48 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	char	c;
	int		printed;

	printed = 0;
	while (*str != '\0')
	{
		c = *str;
		if (ft_putchar(c) == -1)
			return (-1);
		printed++;
		str++;
	}
	return (printed);
}
