/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_num_lower.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:25:18 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/02 15:34:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*create_hexa_str(unsigned int num)
{
	char	*new_str;
	char	hexa[17];
	size_t	new_len;

	ft_strlcpy(hexa, "0123456789abcdef", 17);
	new_len = (size_t) ft_numlen((unsigned long long) num, 16);
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	new_str[new_len] = '\0';
	if (num == 0)
		new_str[new_len - 1] = '0';
	while (num != 0)
	{
		new_str[new_len - 1] = hexa[num % 16];
		new_len--;
		num = num / 16;
	}
	return (new_str);
}

static char	*apply_precision(char *str, unsigned int num, int prec)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(str);
	if ((prec > (int) len) || (prec == 0 && num == 0))
	{
		new_str = (char *) malloc (prec + 1);
		if (!new_str)
			return (NULL);
		new_str[prec] = '\0';
		if (prec != 0)
		{
			ft_memset(new_str, '0', prec);
			ft_memcpy(&new_str[prec - len], str, len);
		}
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

static char	*apply_0x_hexa(char *str, char *s, int prec, unsigned int num)
{
	char	*new_str;
	size_t	len;
	size_t	new_len;

	if (ft_flag(s, '#') && (prec != 0) && (num != 0))
	{
		len = ft_strlen(str);
		new_len = len + 2;
		new_str = (char *) malloc (new_len + 1);
		if (!new_str)
			return (NULL);
		new_str[0] = '0';
		new_str[1] = 'x';
		new_str[new_len] = '\0';
		ft_memcpy(&new_str[new_len - len], str, len);
	}
	else
		new_str = ft_strdup(str);
	return (new_str);
}

static char	*apply_min_field(char *str, char *s, size_t min, unsigned int n)
{
	char	*new_str;
	char	c;

	if (min <= ft_strlen(str))
		return (ft_strdup(str));
	new_str = (char *) malloc (min + 1);
	if (!new_str)
		return (NULL);
	new_str[min] = '\0';
	c = ' ';
	if (ft_flag(s, '0') && !ft_strcontains(s, '.'))
		c = '0';
	ft_memset(new_str, c, min);
	if (ft_flag(s, '-'))
		ft_memcpy(new_str, str, ft_strlen(str));
	else if (c == 0 && ft_flag(s, '#') && n != 0)
	{
		new_str[0] = '0';
		new_str[1] = 'x';
		ft_memcpy(&new_str[min - ft_strlen(str) + 2],
			&str[2], ft_strlen(str) - 2);
	}
	else
		ft_memcpy(&new_str[min - ft_strlen(str)], str, ft_strlen(str));
	return (new_str);
}

char	*ft_hexa_num_lower(char *s, va_list args)
{
	unsigned int	num;
	char			*str;
	char			*str_2;
	size_t			min_field;
	int				prec;

	num = va_arg(args, unsigned int);
	str = create_hexa_str(num);
	if (!str)
		return (NULL);
	prec = -1;
	if (ft_strcontains(s, '.'))
		prec = (int) ft_cal_prec(s);
	str_2 = apply_precision(str, num, prec);
	free (str);
	if (!str_2)
		return (NULL);
	str = apply_0x_hexa(str_2, s, prec, num);
	free(str_2);
	if (!str)
		return (NULL);
	min_field = ft_cal_min_field(s);
	str_2 = apply_min_field(str, s, min_field, num);
	free(str);
	return (str_2);
}
