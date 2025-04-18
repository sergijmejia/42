/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:01:01 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:37:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_character(const char *s)
{
	while (*s && ft_strcontains("-0.# +123456789", *s))
		s++;
	if (*s == 'c')
		return (1);
	else
		return (0);
}

static int	literal_char(const char **s)
{
	if (ft_putchar(**s) == -1)
		return (-1);
	(*s)++;
	return (1);
}

static int	double_percent(const char **s)
{
	if (ft_putchar(**s) == -1)
		return (-1);
	*s = *s + 2;
	return (1);
}

static int	argument(const char **s, va_list args)
{
	char	*arg;
	int		printed;

	arg = NULL;
	if (check_character(&(*s)[1]) == 1)
	{
		ft_create_character_arg(&(*s)[1], args, &arg);
		if (!arg)
			return (-1);
		if (arg[0] == '\0')
			printed = ft_putstr(&arg[1]) + 1;
		else
			printed = ft_putstr(arg);
	}
	else
	{
		ft_create_arg(*s, args, &arg);
		if (!arg)
			return (-1);
		printed = ft_putstr(arg);
	}
	*s = *s + ft_count_arg_len(&(*s)[1]) + 1;
	free(arg);
	return (printed);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		printed;
	int		arg_printed;

	va_start(args, s);
	printed = 0;
	while (*s)
	{
		if (*s != '%')
			arg_printed = literal_char(&s);
		else if (s[1] == '%')
			arg_printed = double_percent(&s);
		else
			arg_printed = argument(&s, args);
		if (arg_printed == -1)
		{
			printed = arg_printed;
			break ;
		}
		else
			printed = printed + arg_printed;
	}
	va_end(args);
	return (printed);
}
