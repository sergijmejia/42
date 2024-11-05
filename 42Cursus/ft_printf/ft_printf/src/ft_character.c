/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_character.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:52:17 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/02 14:42:53 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_character(char *s, va_list args)
{
	char	*str;
	size_t	min_field;
	size_t	len;

	min_field = ft_cal_min_field(s);
	if (ft_flag(s, '-') && (min_field > 1))
		len = min_field;
	else
		len = 1;
	str = (char *) malloc (len + 1);
	if (!str)
		return (NULL);
	ft_memset(str, ' ', len);
	str[0] = (char) va_arg(args, int);
	str[len] = '\0';
	return (str);
}
