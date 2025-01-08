/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 02:15:10 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:42:34 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*apply_zero_prec(char *str, int num, size_t len, int prec)
{
	char	*new_str;
	size_t	new_len;

	new_len = (size_t) prec;
	if (num < 0)
		new_len++;
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	ft_memset(new_str, '0', new_len);
	new_str[new_len] = '\0';
	if (num >= 0)
		ft_memcpy(&new_str[new_len - len], str, len);
	else
	{
		new_str[0] = '-';
		ft_memcpy(&new_str[new_len - len + 1], &str[1], len - 1);
	}
	return (new_str);
}

static char	*apply_precision(char *str, int num, int prec)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(str);
	if (prec >= (int) len)
	{
		new_str = apply_zero_prec(str, num, len, prec);
		if (!new_str)
			return (NULL);
	}
	else if (prec == 0 && num == 0)
	{
		new_str = (char *) malloc (1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
	}
	else
	{
		new_str = (char *) malloc (len + 1);
		if (!new_str)
			return (NULL);
		ft_memcpy(new_str, str, len + 1);
	}
	return (new_str);
}

static char	*apply_signal(char *str, char *s, int num)
{
	char	*new_str;
	size_t	new_len;
	size_t	len;

	len = ft_strlen(str);
	if ((ft_flag(s, '+') || ft_flag(s, ' ')) && (num >= 0))
	{
		new_len = len + 1;
		new_str = (char *) malloc (new_len + 1);
		if (!new_str)
			return (NULL);
		if (ft_flag(s, '+'))
			new_str[0] = '+';
		else
			new_str[0] = ' ';
		new_str[new_len] = '\0';
		ft_memcpy(&new_str[1], str, len);
	}
	else
		new_str = ft_strdup(str);
	return (new_str);
}

char	*ft_integer(char *s, va_list args)
{
	char	*str;
	char	*str_2;
	size_t	min_field;
	int		num;
	int		prec;

	num = va_arg(args, int);
	str = ft_itoa(num);
	if (!str)
		return (NULL);
	prec = -1;
	if (ft_strcontains(s, '.'))
		prec = (int) ft_cal_prec(s);
	str_2 = apply_precision(str, num, prec);
	free(str);
	if (!str_2)
		return (NULL);
	str = apply_signal(str_2, s, num);
	free(str_2);
	if (!str)
		return (NULL);
	min_field = ft_cal_min_field(s);
	str_2 = ft_apply_min_field_int(str, s, num, min_field);
	free(str);
	return (str_2);
}
