/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_character_arg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:18:37 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:44:40 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_create_character_arg(const char *s, va_list args, char **arg)
{
	char	*str;
	size_t	min_field;
	int		len;

	str = (char *) s;
	min_field = ft_cal_min_field(str);
	if (min_field > 1)
		len = (int) min_field;
	else
		len = 1;
	*arg = (char *) malloc (len + 1);
	if (!*arg)
		return (-1);
	ft_memset(*arg, ' ', len);
	if (!ft_flag(str, '-'))
		(*arg)[len - 1] = (char) va_arg(args, int);
	else
		(*arg)[0] = (char) va_arg(args, int);
	(*arg)[len] = '\0';
	return (len);
}
