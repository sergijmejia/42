/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:37:19 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/01 17:37:19 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*cpy_arg(char *s)
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

static char	*create_print_arg(char *s, va_list args)
{
	char	*arg;
	char	c;

	c = s[ft_strlen(s) - 1];
	if (c == 'c')
		arg = character(s, args);
	if (c == 's')
		arg = string(s, args);
	if (c == 'p')
		arg = hexa_pointer(s, args);
	if (c == 'd')
		arg = integer(s, args);
	if (c == 'i')
		arg = integer(s, args);
	if (c == 'u')
		arg = unsig_int(s, args);
	if (c == 'x')
		arg = hexa_num_lower(s, args);
	if (c == 'X')
		arg = hexa_num_upper(s, args);
	return (arg);
}

char	*ft_create_arg(char *s, va_list args)
{
	char	*str;
	char	*print;
	size_t	len;

	str = cpy_arg(s);
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (!check_arg(str))
	{
		print = (char *) malloc (len + 1);
		if (!print)
		{
			free(str);
			return (NULL);
		}
		print[len] = '\0';
		ft_memcpy(print, str, len);
		free(str);
		return (print);
	}
	print = create_print_arg(&str[1], args);
	free(str);
	return (print);
}
