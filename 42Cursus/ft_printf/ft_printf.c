/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:01:01 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/01 17:01:01 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	literal_char(char **s)
{
	ft_putchar(**s);
	(*s)++;
	return (1);
}

static int	double_percent(char **s)
{
	ft_putchar(**s);
	*s = *s + 2;
	return (1);
}

static int	argument(char **s, va_list args)
{
	char	*arg;
	int		printed;

	arg = ft_create_arg(*s, args);
	if (!arg)
	{
		va_end(args);
		return (-1);
	}
	printed = ft_strlen(arg);
	*s = *s + ft_count_arg_len(&(*s)[1]) + 1;
	ft_putstr(arg);
	free(arg);
	return (printed);
}

int	ft_printf(char *s, ...)
{
	va_list	args;
	int		printed;

	va_start(args, s);
	printed = 0;
	while (*s)
	{
		if (*s != '%')
			printed = printed + literal_char(&s);
		else if (s[1] == '%')
			printed = printed + double_percent(&s);
		else
			printed = printed + argument(&s, args);
	}
	va_end(args);
	return (printed);
}
