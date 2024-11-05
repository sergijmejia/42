/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:35:46 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/05 17:23:07 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*apply_precision(char *s, char *str)
{
	char	*new_str;
	size_t	len;
	size_t	new_len;

	len = ft_strlen(str);
	if (ft_strcontains(s, '.'))
		new_len = ft_cal_prec(s);
	else
		new_len = len;
	if (new_len > len)
		new_len = len;
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, new_len + 1);
	return (new_str);
}

static char	*apply_min_field(char *s, char *str)
{
	char	*new_str;
	size_t	len;
	size_t	new_len;

	len = ft_strlen(str);
	new_len = ft_cal_min_field(s);
	if (new_len <= len)
		return (ft_strdup(str));
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	ft_memset(new_str, ' ', new_len);
	if (ft_flag(s, '-'))
		ft_memcpy(new_str, str, len);
	else
		ft_memcpy(&new_str[new_len - len], str, len);
	new_str[new_len] = '\0';
	return (new_str);
}

char	*ft_string(char *s, va_list args)
{
	char	*str;
	char	*str_temp;
	size_t	len;

	str = va_arg(args, char *);
	if (!*str)
		return (-1);
	str_temp = apply_precision(s, str);
	if (!str_temp)
		return (-1);
	str = str_temp;
	str_temp = apply_min_field(s, *str);
	free(*str);
	if (!str_temp)
		return (-1);
	str = str_temp;
	return (str);
}
