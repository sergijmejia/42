/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:37:19 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:39:45 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	if (ft_strcontains("cspdiuxX%", s[i]))
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

static char	*create_print_arg(char *s, va_list args)
{
	char	*arg;
	char	c;

	c = s[ft_strlen(s) - 1];
	if (c == 's')
		arg = ft_string(s, args);
	if (c == 'p')
		arg = ft_hexa_pointer(s, args);
	if (c == 'd')
		arg = ft_integer(s, args);
	if (c == 'i')
		arg = ft_integer(s, args);
	if (c == 'u')
		arg = ft_unsig_int(s, args);
	if (c == 'x')
		arg = ft_hexa_num_lower(s, args);
	if (c == 'X')
		arg = ft_hexa_num_upper(s, args);
	if (c == '%')
		arg = ft_strdup("%");
	return (arg);
}

int	ft_create_arg(const char *s, va_list args, char **arg)
{
	char	*str;
	size_t	len_arg;

	str = cpy_arg(s);
	if (!str)
		return (-1);
	if (!check_arg(str))
	{
		free(str);
		return (-1);
	}
	*arg = create_print_arg(&str[1], args);
	free(str);
	if (!*arg)
		return (-1);
	len_arg = ft_strlen(*arg);
	return ((int) len_arg);
}
