/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:06:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/10 16:15:32 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;

	n = ft_strlen(src);
	if ((dst == NULL) || (src == NULL) || (size == 0))
		return (n);
	if (n >= (size - 1))
	{
		dst = ft_memcpy(dst, src, (size - 1));
		dst[size - 1] = '\0';
	}
	else
	{
		dst = ft_memcpy(dst, src, n);
		dst[n] = '\0';
	}
	return (n);
}
