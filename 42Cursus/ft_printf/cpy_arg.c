/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:50:09 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/28 18:41:46 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	cout_arg_len(char *s)
{
	size_t	len;

	len = 0;
	while (*s && ft_strcontains("-0.# +123456789", *s))
	{
		len++;
		s++;
	}
	if (*s && ft_strcontains("cspdiuxX", *s))
	{
		len++;
		s++;
	}
	return (len);
}

char	*cpy_arg(char *s)
{
	size_t	len;
	char	*arg;
	
	len = count_arg_len(s + 1) + 1;
	arg = (char *) malloc (len + 1);
	if (!arg)
		return (NULL);
	arg = ft_strlcpy(arg, s, len);
	arg[len] = '\0';
	return (arg);
}

int	check_arg(char *s)
{
	size_t	i;

	i = ft_strlen(s);
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

int	numlen(unsigned long long n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

/*FUNCIONES PARA CALCULAR PRECISION Y MIN_FIELD*/

size_t	cal_prec(char *s)
{
	char	*str;
	size_t	prec;

	prec = 0;
	if (ft_strcontains(s, '.'))
	{
		str = ft_strrchr(s, '.') + 1;
		while (ft_isdigit(*str))
		{
			prec = prec * 10 + (*str - '0');
			str++;
		}
	}
	return (prec);
}

size_t	cal_min_field(char *s)
{
	size_t	min_field;

	min_field = 0;
	while (ft_strcontains("-0# +", *s))
		s++;
	while (ft_isdigit(*s))
	{
		min_field = min_field * 10 + (*s - '0');
		s++;
	}
	return (min_field);
}

/*FUNCIONES PARA SABER SI CONTIENE LAS FLAGS*/

int	flag(char *s, char c)
{
	while (!ft_strcontains(".123456789cspdiuxX", *s))
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

/*FUNCIONES PARA IDENTFICAR EL TIPO DE ARGUMENTO A IMPRIMIR*/

char	*character(char *s, va_list args)
{
	char	*str;
	size_t	min_field;
	size_t	len;

	min_field = cal_min_field(s);
	if (flag(s, '-') && (min_field > 1))
		len = min_field;
	else
		len = 1;
	str = (char *) malloc (len + 1);
	if (!str)
		return (NULL);
	ft_memset(str, ' ', len);
	str[0] = (char) va_arg(args, int);
	str[len] = '\0';
	return (str);
}

char	*string(char *s, va_list args)
{
	char	*str;
	char	*str_2;
	size_t	min_field;
	size_t	len;

	min_field = cal_min_field(s);
	str = va_arg(args, char *);
	if (ft_strcontains(s, '.'))
		len = cal_prec(s); 
	else 
		len = ft_strlen(str);
	str_2 = (char *) malloc (len + 1);
	ft_strlcpy(str_2, str, len + 1);
	if (min_field > len)
		str = (char *) malloc (min_field + 1);
	else
		return (str_2);
	ft_memset(str, ' ', min_field);
	if (flag(s, '-'))
		ft_memcpy(str, str_2, min_field - 1);
	else
		ft_memcpy(&str[min_field - len], str_2, len);
	free(str_2);
	return (str);
}

char	*hexa_pointer(va_list args)
{
	void				*pnt;
	unsigned long long	num_pnt;
	char				*str;
	char				hexa[17];
	int					len;

	pnt = va_arg(args, void*);
	num_pnt = (unsigned long long) pnt;
	ft_strlcpy(hexa, "0123456789abcdef", 17);
	len = numlen(num_pnt, 16);
	str = (char *) malloc (len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num_pnt == 0)
		str[len - 1] = '0';
	while (num_pnt != 0)
	{
		str[len - 1] = hexa[num_pnt % 16];
		len--;
		num_pnt = num_pnt / 16;
	}
	return (str);
}

char	*unsig_int(va_list args)
{
	char			*str;
	int				len;
	unsigned int	num;

	num = va_arg(args, unsigned int);
	len = numlen((unsigned long long) num, 10);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (num != 0)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}

char	*hexa_num_lower(va_list args)
{
	unsigned int	num;
	char			*str;
	char			hexa[17];
	int				len;
	
	num = va_arg(args, unsigned int);
	ft_strlcpy(hexa, "0123456789abcdef", 17);
	len = numlen(num, 16);
	str = (char *) malloc (len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num == 0)
		str[len - 1] = '0';
	while (num_pnt != 0)
	{
		str[len - 1] = hexa[num % 16];
		len--;
		num = num / 16;
	}
	return (str);
}

char	*hexa_num_upper(va_list args)
{
	char	*str;

	str = hexa_num_lower(args);
	ft_strtoupper(arg);
	return (str);
}

char	*arg_to_str(char *s, va_list args)
{
	char	*arg;
	char	c;

	c = s[ft_strlen(s) - 1];
	if (c == 'c')
		arg = character(s, args);
	if (c == 's')
		arg = string(s, args);
	if (c == 'p')
		arg = hexa_pointer(args);
	if (c == 'd'|| c == 'i')
		arg = ft_itoa(va_arg(args, int));
	if (c == 'u')
		arg = unsig_int(args);
	if (x == 'x')
		arg = hexa_num_lower(args);
	if (x == 'X')
		arg = hexa_num_upper(args);
	return (arg);
}

/*FUNCION PARA CREAR EL ARGUMENTO A IMPRIMIR*/

char	*create_print_arg(char *s, va_list args)
{
	char	*arg;
	size_t	min_field;
	size_t	prec;

	arg = arg_to_str(s, args);
	prec = cal_prec(s);
	min_field = cal_min_field(s);
	


	return (arg);

}

char	*create_arg(char *s, va_list args)
{
	char	*str;
	char	*print;

	if (*s != '%')
		return (NULL);
	str = cpy_arg(s);
	if (!str)
		return (NULL);
	if (!check_arg(str))
		return (str);
	arg_to_print = create_print_arg(str, args);
	return (arg_to_print);
}

