/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:37:19 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/05 18:01:45 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*cpy_arg(const char *s)
{
	size_t	len;
	char	*arg;

	len = ft_count_arg_len(&s[1]) + 1;
	arg = (char *) malloc (len + 1);
	if (!arg)
		return (NULL);
	ft_strlcpy(arg, s, len + 1);
	arg[len] = '\0';
	return (arg);
}

static int	check_arg(char *s)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	if (ft_strcontains("cspdiuxX", s[i]))
		i--;
	else
		return (0);
	while (ft_isdigit(s[i]))
		i--;
	if (s[i] == '.')
	{
		i--;
		while (ft_isdigit(s[i]))
			i--;
	}
	while (ft_strcontains("-0.# +", s[i]))
		i--;
	if (s[i] == '%')
		return (1);
	else
		return (0);
}

static int	*create_print_arg(char *s, va_list args, char **arg)
{
	char	c;
	int		len;

	c = s[ft_strlen(s) - 1];
	if ((c == 'c') || (c == 's'))
		len = ft_create_print_arg_cs(s, args, *arg, c);
	if ((c == 'p') || (c == 'd') || (c == 'i'))
		len = ft_create_print_arg_pdi(s, args, *arg, c);
	if ((c == 'u') || (c == 'x') || (c == 'X'))
		len = ft_create_print_arg_ux(s, args, *arg, c);
	return (len);
}

int	ft_create_arg(const char *s, va_list args, char **print)
{
	char	*str;
	int	len;

	str = cpy_arg(s);
	if (!str)
		return (-1);
	len = (int) ft_strlen(str);
	if (!check_arg(str))
	{
		*print = (char *) malloc (len + 1);
		if (!*print)
		{
			free(str);
			return (-1);
		}
		*print[len] = '\0';
		ft_memcpy(*print, str, len);
	}
	else
		len = create_print_arg(&str[1], args, *print);
	free(str);
	return (len);
}
