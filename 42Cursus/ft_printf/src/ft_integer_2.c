/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 02:15:10 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/02 15:11:41 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	apply_zero_signal(char *new_str, char *str, char *s, int num)
{
	size_t	len;
	size_t	new_len;

	len = ft_strlen(str);
	new_len = ft_cal_min_field(s);
	if (num >= 0)
	{
		if (ft_flag(s, '+') || ft_flag(s, ' '))
		{
			if (ft_flag(s, '+'))
				new_str[0] = '+';
			else
				new_str[0] = ' ';
			ft_memcpy(&new_str[new_len - len + 1], &str[1], len - 1);
		}
		else
			ft_memcpy(&new_str[new_len - len], str, len);
	}
	else
	{
		new_str[0] = '-';
		ft_memcpy(&new_str[new_len - len + 1], &str[1], len - 1);
	}
}

char	*ft_apply_min_field_int(char *str, char *s, int num, size_t min_field)
{
	char	*new_str;
	char	c;
	size_t	len;

	len = ft_strlen(str);
	if (min_field > len)
	{
		new_str = (char *) malloc (min_field + 1);
		if (!new_str)
			return (NULL);
		new_str[min_field] = '\0';
		c = ' ';
		if (ft_flag(s, '0') && !ft_strcontains(s, '.'))
			c = '0';
		ft_memset(new_str, c, min_field);
		if (ft_flag(s, '-'))
			ft_memcpy(new_str, str, len);
		else if (c == 0)
			apply_zero_signal(new_str, str, s, num);
		else
			ft_memcpy(&new_str[min_field - len], str, len);
	}
	else
		new_str = ft_strdup(str);
	return (new_str);
}
