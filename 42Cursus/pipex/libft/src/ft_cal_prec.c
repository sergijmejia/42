/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cal_prec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:12:53 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:38:35 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_cal_prec(char *s)
{
	char	*str;
	size_t	prec;

	prec = 0;
	if (ft_strcontains(s, '.'))
	{
		str = ft_strrchr(s, '.') + 1;
		while (ft_isdigit(*str))
		{
			prec = prec * 10 + (*str - '0');
			str++;
		}
	}
	return (prec);
}
