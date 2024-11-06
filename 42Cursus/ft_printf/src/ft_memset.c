/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:59:25 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/14 18:46:00 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*aux;
	size_t			i;

	if (num == 0)
		return (ptr);
	aux = (unsigned char *) ptr;
	i = 0;
	while (i < num)
	{
		*aux = (unsigned char) value;
		aux++;
		i++;
	}
	return (ptr);
}
