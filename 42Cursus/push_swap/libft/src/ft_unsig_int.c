/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsig_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:32:38 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:43:35 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_unsigned_int(unsigned int num)
{
	char	*new_str;
	size_t	new_len;

	new_len = (size_t) ft_numlen((unsigned long long) num, 10);
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	new_str[new_len] = '\0';
	if (num == 0)
		new_str[new_len - 1] = '0';
	while (num != 0)
	{
		new_str[new_len - 1] = (num % 10) + '0';
		new_len--;
		num = num / 10;
	}
	return (new_str);
}

static char	*apply_zero_prec(char *str, int prec)
{
	char	*new_str;
	size_t	new_len;
	size_t	len;

	len = ft_strlen(str);
	new_len = (size_t) prec;
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	ft_memset(new_str, '0', new_len);
	new_str[new_len] = '\0';
	ft_memcpy(&new_str[new_len - len], str, len);
	return (new_str);
}

static char	*apply_precision(char *str, unsigned int num, int prec)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(str);
	if (prec > (int) len)
	{
		new_str = apply_zero_prec(str, prec);
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

static char	*apply_min_field(char *str, char *s, size_t min_field)
{
	char	*new_str;
	char	c;
	size_t	len;

	c = ' ';
	if (ft_flag(s, '0') && !ft_strcontains(s, '.') && !ft_flag(s, '-'))
		c = '0';
	len = ft_strlen(str);
	if (min_field > len)
	{
		new_str = (char *) malloc (min_field + 1);
		if (!new_str)
			return (NULL);
		new_str[min_field] = '\0';
		ft_memset(new_str, c, min_field);
		if (ft_flag(s, '-'))
			ft_memcpy(new_str, str, len);
		else
			ft_memcpy(&new_str[min_field - len], str, len);
	}
	else
		new_str = ft_strdup(str);
	return (new_str);
}

char	*ft_unsig_int(char *s, va_list args)
{
	unsigned int	num;
	char			*str;
	char			*str_2;
	size_t			min_field;
	int				prec;

	num = va_arg(args, unsigned int);
	str = create_unsigned_int(num);
	if (!str)
		return (NULL);
	prec = -1;
	if (ft_strcontains(s, '.'))
		prec = (int) ft_cal_prec(s);
	str_2 = apply_precision(str, num, prec);
	free(str);
	if (!str_2)
		return (NULL);
	min_field = ft_cal_min_field(s);
	str = apply_min_field(str_2, s, min_field);
	free(str_2);
	return (str);
}
