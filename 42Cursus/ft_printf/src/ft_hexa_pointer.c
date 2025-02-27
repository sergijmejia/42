/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:35:46 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/11 10:18:31 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*create_hexa_str(unsigned long long num)
{
	char	*new_str;
	char	hexa[17];
	size_t	new_len;

	if (num == 0)
	{
		new_str = ft_strdup("(nil)");
		if (!new_str)
			return (NULL);
		return (new_str);
	}
	ft_strlcpy(hexa, "0123456789abcdef", 17);
	new_len = (size_t) ft_numlen(num, 16);
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	new_str[new_len] = '\0';
	while (num != 0)
	{
		new_str[new_len - 1] = hexa[num % 16];
		new_len--;
		num = num / 16;
	}
	return (new_str);
}

static char	*apply_precision(char *s, char *str)
{
	char	*new_str;
	size_t	len;
	size_t	new_len;

	len = ft_strlen(str);
	new_len = ft_cal_prec(s);
	if (new_len <= len)
		return (ft_strdup(str));
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	ft_memset(new_str, '0', new_len);
	ft_memcpy(&new_str[new_len - len], str, len);
	new_str[new_len] = '\0';
	return (new_str);
}

static char	*add_0x_hexa(char *str)
{
	char	*new_str;
	size_t	len;
	size_t	new_len;

	len = ft_strlen(str);
	new_len = len + 2;
	new_str = (char *) malloc (new_len + 1);
	if (!new_str)
		return (NULL);
	ft_memset(new_str, '0', new_len);
	new_str[1] = 'x';
	new_str[new_len] = '\0';
	ft_memcpy(&new_str[new_len - len], str, len);
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

char	*ft_hexa_pointer(char *s, va_list args)
{
	unsigned long long	num_pnt;
	void				*pnt;
	char				*str;
	char				*str_2;

	pnt = va_arg(args, void *);
	num_pnt = (unsigned long long) pnt;
	str = create_hexa_str(num_pnt);
	if (ft_memcmp(str, "(nil)", ft_strlen(str) + 1) == 0)
		str_2 = ft_strdup(str);
	else
	{
		str_2 = apply_precision(s, str);
		free(str);
		if (!str_2)
			return (NULL);
		str = str_2;
		str_2 = add_0x_hexa(str);
	}
	free(str);
	if (!str_2)
		return (NULL);
	str = apply_min_field(s, str_2);
	free(str_2);
	return (str);
}
