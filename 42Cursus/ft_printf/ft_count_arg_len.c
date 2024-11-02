/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_arg_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:06:32 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/02 14:44:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_count_arg_len(char *s)
{
	size_t	len;

	len = 0;
	while (*s && ft_strcontains("-0.# +123456789", *s))
	{
		len++;
		s++;
	}
	if (*s && ft_strcontains("cspdiuxX", *s))
	{
		len++;
		s++;
	}
	return (len);
}
