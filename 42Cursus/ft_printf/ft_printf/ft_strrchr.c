/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:54:12 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/14 19:07:00 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	chr;
	const char		*str;
	int				pos;	

	str = NULL;
	chr = (unsigned char) c;
	pos = ft_strlen(s);
	while (pos >= 0)
	{
		if (s[pos] == chr)
		{
			str = &s[pos];
			break ;
		}
		pos--;
	}
	return ((char *) str);
}
