/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:35:46 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/10 02:45:21 by smejia-a         ###   ########.fr       */
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
	{
		new_len = ft_cal_prec(s);
		if ((ft_memcmp(str, "(null)", 7) == 0) && (new_len < 6))
			return (ft_strdup(""));
	}
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
	size_t	len_temp;

	str_temp = va_arg(args, char *);
	if (!str_temp)
		str = ft_strdup("(null)");
	else
	{
		len_temp = ft_strlen(str_temp);
		str = (char *) malloc (len_temp + 1);
		ft_memcpy(str, str_temp, len_temp);
		str[len_temp] = '\0';
	}
	str_temp = apply_precision(s, str);
	free(str);
	if (!str_temp)
		return (NULL);
	str = str_temp;
	str_temp = apply_min_field(s, str);
	free(str);
	if (!str_temp)
		return (NULL);
	str = str_temp;
	return (str);
}
