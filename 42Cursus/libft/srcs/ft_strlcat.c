/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:25:11 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/26 19:58:52 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			len_d;
	size_t			len_s;
	size_t			len_need;
	unsigned char	*d;

	len_d = ft_strlen(dst);
	len_s = ft_strles(src);
	len_need = len_d + len_s + 1;
	d = dest[len_d];
	if (len_need <= size)
	{
		while (src != '\0')
		{
			*d = *src;
			src++;
		}
	}
	else
	{
		while (len_d < size)
		{
			d[len_d] = *src;
			len_d++;
			src++;
		}
	}
	return (len_need);
}
