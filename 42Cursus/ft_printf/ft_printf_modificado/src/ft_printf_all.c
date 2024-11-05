/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:13:03 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/01 13:49:19 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>

size_t	count_arg_len(char *s)
{
	size_t	len;

	//printf("\n__(entra en la funcion count_arg_len)__\n");
	//printf("\n_ (el string recibido en count_arg_len es: %s)_\n ", s);
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
	//printf("\n_ (el valor de len de ese string es: %d)_\n ", (int) len);
	return (len);
}

char	*cpy_arg(char *s)
{
	size_t	len;
	char	*arg;

	//printf("\n__(entra en la funcion cpy_arg)__\n");
	len = count_arg_len(&s[1]) + 1;
	//printf("\n_ (el valor de len en cpy_arg es: %d)_\n ", (int) len);
	arg = (char *) malloc (len + 1);
	if (!arg)
		return (NULL);
	ft_strlcpy(arg, s, len + 1);
	arg[len] = '\0';
	return (arg);
}

int	check_arg(char *s)
{
	size_t	i;

	//printf("\n__(entra en la funcion check_arg)__\n");
	i = ft_strlen(s) - 1;
	//printf("\n__(la longitud del string es: %d)__\n", (int) i);
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
	{
		//printf("\n__(la funcion check_arg da OK el string)__\n");
		return (1);
	}
	else
	{
		//printf("\n__(la funcion check_arg da NOK el string)__\n");
		return (0);
	}
}

int	numlen(unsigned long long n, int base)
{
	int	len;

	//printf("\n__(entra en la funcion numlen)__\n");
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

	//printf("\n__(entra en la funcion cal_prec)__\n");
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

	//printf("\n__(entra en la funcion cal_min_field)__\n");
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

/*FUNCION PARA SABER SI CONTIENE LAS FLAGS*/

int	flag(char *s, char c)
{
	//printf("\n__(entra en la funcion flag)__\n");
	while (!ft_strcontains(".123456789cspdiuxX", *s))
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

/*FUNCION PARA OBTENER LAS FLAGS*/

char	*get_flags(char *s)
{
	char	*flags;
	size_t	len;

	//printf("\n__(entra en la funcion get_flags)__\n");
	len = 0;
	while (ft_strcontains("-0# +", s[len]))
		len++;
	flags = (char *) malloc (len + 1);
	if (!flags)
		return (NULL);
	flags[len] = '\0';
	if (len != 0)
		ft_memcpy(flags, s, len);
	return (flags);
}

/*FUNCIONES PARA IDENTFICAR EL TIPO DE ARGUMENTO A IMPRIMIR*/

char	*character(char *s, va_list args)
{
	char	*str;
	size_t	min_field;
	size_t	len;

	//printf("\n__(entra en la funcion character)__\n");
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
	size_t	len_2;

	//printf("\n__(entra en la funcion string)__\n");
	min_field = cal_min_field(s);
	str = va_arg(args, char *);
	len = ft_strlen(str);
	if (ft_strcontains(s, '.'))
		len_2 = cal_prec(s);
	else
		len_2 = len;
	if (len_2 > len)
		len_2 = len;
	str_2 = (char *) malloc (len_2 + 1);
	if (!str_2)
		return (NULL);
	str_2[len_2] = '\0';
	ft_strlcpy(str_2, str, len_2 + 1);
	str = str_2;
	len = len_2;
	if (min_field > len)
	{
		len_2 = min_field;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		ft_memset(str_2, ' ', len_2);
		if (flag(s, '-'))
			ft_memcpy(str_2, str, len);
		else
			ft_memcpy(&str_2[len_2 - len], str, len);
		str_2[len_2] = '\0';
		free(str);
		str = str_2;
	}
	return (str);
}

char	*hexa_pointer(char *s, va_list args)
{
	void				*pnt;
	unsigned long long	num_pnt;
	char				*str;
	char				*str_2;
	char				hexa[17];
	size_t				len;
	size_t				len_2;

	//printf("\n__(entra en la funcion hexa_pointer)__\n");
	pnt = va_arg(args, void *);
	num_pnt = (unsigned long long) pnt;
	ft_strlcpy(hexa, "0123456789abcdef", 17);
	len = (size_t) numlen(num_pnt, 16);
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
	len = ft_strlen(str);
	len_2 = len + 2;
	str_2 = (char *) malloc (len_2 + 1);
	if (!str_2)
	{
		free(str);
		return (NULL);
	}
	ft_memset(str_2, '0', len_2);
	str_2[1] = 'x';
	str_2[len_2] = '\0';
	ft_memcpy(&str_2[len_2 - len], str, len);
	free(str);
	str = str_2;
	len = len_2;
	len_2 = cal_min_field(s);
	if (len_2 > len)
	{
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		str_2[len_2] = '\0';
		ft_memset(str_2, ' ', len_2);
		if (ft_strcontains(s, '-'))
			ft_memcpy(str_2, str, len);
		else
			ft_memcpy(&str_2[len_2 - len], str, len);
		free(str);
		str = str_2;
	}
	return (str);
}

char	*integer(char *s, va_list args)
{
	char	*str;
	char	*str_2;
	char	*flags;
	int		num;
	size_t	min_field;
	size_t	len;
	size_t	len_2;
	int		prec;

	//printf("\n__(entra en la funcion integer)__\n");
	flags = get_flags(s);
	if (!flags)
		return (NULL);
	num = va_arg(args, int);
	str = ft_itoa(num);
	len = ft_strlen(str);
	prec = -1;
	if (ft_strcontains(s, '.'))
		prec = (int) cal_prec(s);
	if (prec > (int) len)
	{
		len_2 = (size_t) prec;
		if (num < 0)
			len_2++;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		ft_memset(str_2, '0', len_2);
		str_2[len_2] = '\0';
		if (num >= 0)
			ft_memcpy(&str_2[len_2 - len], str, len);
		else
		{
			str_2[0] = '-';
			ft_memcpy(&str_2[len_2 - len + 1], &str[1], len - 1);
		}
	}
	else if ((prec == 0) && (num == 0))
	{
		len_2 = 0;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		str_2[len_2] = '\0';
	}
	else
	{
		len_2 = len;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		ft_memcpy(str_2, str, len);
		str_2[len_2] = '\0';
	}
	free(str);
	str = str_2;
	len = len_2;
	if ((ft_strcontains(flags, '+') || ft_strcontains(flags, ' ')) && (num >= 0))
	{
		len_2 = len + 1;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		if (ft_strcontains(flags, '+'))
			str_2[0] = '+';
		else
			str_2[0] = ' ';
		str_2[len_2] = '\0';
		ft_memcpy(&str_2[1], str, len);
		free(str);
		str = str_2;
		len = len_2;
	}
	min_field = cal_min_field(s);
	if (min_field > len)
	{
		len_2 = min_field;
		if (ft_strcontains(flags, '-'))
		{
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, ' ', len_2);
			ft_memcpy(str_2, str, len);
		}
		else if (ft_strcontains(flags, '0') && !ft_strcontains(s, '.'))
		{
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, '0', len_2);
			if (ft_strcontains(flags, '+') && num >= 0)
			{
				str_2[0] = '+';
				ft_memcpy(&str_2[len_2 - len + 1], &str[1], len - 1);
			}
			else if (ft_strcontains(flags, ' ') && num >= 0)
			{
				str_2[0] = ' ';
				ft_memcpy(&str_2[len_2 - len + 1], &str[1], len - 1);
			}
			else if (num >= 0)
				ft_memcpy(&str_2[len_2 - len], str, len);
			else
			{
				str_2[0] = '-';
				ft_memcpy(&str_2[len_2 - len + 1], &str[1], len - 1);
			}
		}
		else
		{
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, ' ', len_2);
			ft_memcpy(&str_2[len_2 - len], str, len);
		}
		free(str);
		str = str_2;
		len = len_2;
	}
	return (str);
}

char	*unsig_int(char *s, va_list args)
{
	unsigned int	num;
	unsigned int	num_2;
	char			*str;
	char			*str_2;
	char			*flags;
	size_t			len;
	size_t			len_2;
	size_t			min_field;
	int				prec;

	//printf("\n__(entra en la funcion unsig_int)__\n");
	flags = get_flags(s);
	if (!flags)
		return (NULL);
	//printf("\n__(el string flags es: %s)__\n", flags);
	num = va_arg(args, unsigned int);
	//printf("\n__(num es: %u)__\n", num);
	num_2 = num;
	len = numlen((unsigned long long) num, 10);
	//printf("\n__(el valor de len es: %d)__\n", (int) len);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (num_2 == 0)
		str[0] = 0;
	while (num_2 != 0)
	{
		str[len - 1] = (num_2 % 10) + '0';
		num_2 = num_2 / 10;
		len--;
	}
	len = ft_strlen(str);
	//printf("\n__(el string str es: %s. len es: %d)__\n", str, (int) len);
	prec = -1;
	if (ft_strcontains(s, '.'))
		prec = (int) cal_prec(s);
	if (prec > (int) len)
	{
		//printf("\n__(entra en la condicion prec > len con: %d > %d)__\n", prec, (int) len);
		len_2 = (size_t) prec;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		ft_memset(str_2, '0', len_2);
		str_2[len_2] = '\0';
		ft_memcpy(&str_2[len_2 - len], str, len);
	}
	else if ((prec == 0) && (num == 0))
	{
		len_2 = 0;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		str_2[len_2] = '\0';
	}
	else
	{
		len_2 = len;
		//printf("\n__(len_2 es: %d)__\n", (int) len_2);
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		ft_memcpy(str_2, str, len);
		str_2[len_2] = '\0';
	}
	free(str);
	str = str_2;
	len = len_2;
	min_field = cal_min_field(s);
	if (min_field > len)
	{
		//printf("\n__(entra en la condicion min_field > len con: %d > %d)__\n", (int) min_field, (int) len);
		len_2 = min_field;
		if (ft_strcontains(flags, '-'))
		{
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, ' ', len_2);
			ft_memcpy(str_2, str, len);
		}
		else if (ft_strcontains(flags, '0') && !ft_strcontains(s, '.'))
		{
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, '0', len_2);
			ft_memcpy(&str_2[len_2 - len], str, len);
		}
		else
		{
			//printf("\n__(entra en a condicion para completar los ' ')__\n");
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, ' ', len_2);
			ft_memcpy(&str_2[len_2 - len], str, len);
		}
		free(str);
		str = str_2;
		len = len_2;
	}
	return (str);
}

char	*hexa_num_lower(char *s, va_list args)
{
	unsigned int	num;
	unsigned int	temp_num;
	char			*str;
	char			*str_2;
	char			*flags;
	char			hexa[17];
	size_t			len;
	size_t			len_2;
	size_t			min_field;
	int				prec;

	//printf("\n__(entra en la funcion hexa_num_lower)__\n");
	flags = get_flags(s);
	if (!flags)
		return (NULL);
	num = va_arg(args, unsigned int);
	ft_strlcpy(hexa, "0123456789abcdef", 17);
	len = (size_t) numlen(num, 16);
	str = (char *) malloc (len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	temp_num = num;
	if (temp_num == 0)
		str[len - 1] = '0';
	while (temp_num != 0)
	{
		str[len - 1] = hexa[temp_num % 16];
		len--;
		temp_num = temp_num / 16;
	}
	len = ft_strlen(str);
	prec = -1;
	if (ft_strcontains(s, '.'))
		prec = (int) cal_prec(s);
	if (prec > (int) len)
	{
		len_2 = (size_t) prec;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		ft_memset(str_2, '0', len_2);
		str_2[len_2] = '\0';
		ft_memcpy(&str_2[len_2 - len], str, len);
	}
	else if ((prec == 0) && (num == 0))
	{
		len_2 = 0;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		str_2[len_2] = '\0';
	}
	else
	{
		len_2 = len;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		ft_memcpy(str_2, str, len);
		str_2[len_2] = '\0';
	}
	free (str);
	len = len_2;
	str = str_2;
	if (ft_strcontains(flags, '#') && (prec != 0) && (num != 0))
	{
		len_2 = len + 2;
		str_2 = (char *) malloc (len_2 + 1);
		if (!str_2)
		{
			free(str);
			return (NULL);
		}
		str_2[0] = '0';
		str_2[1] = 'x';
		str_2[len_2] = '\0';
		ft_memcpy(&str_2[len_2 - len], str, len);
		free(str);
		str = str_2;
		len = len_2;
	}
	min_field = cal_min_field(s);
	if (min_field > len)
	{
		len_2 = min_field;
		if (ft_strcontains(flags, '-'))
		{
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, ' ', len_2);
			ft_memcpy(str_2, str, len);
		}
		else if (ft_strcontains(flags, '0') && !ft_strcontains(s, '.'))
		{
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, '0', len_2);
			if (ft_strcontains(flags, '#') && num != 0)
			{
				str_2[0] = '0';
				str_2[1] = 'x';
				ft_memcpy(&str_2[len_2 - len + 2], &str[2], len - 2);
			}
			else
				ft_memcpy(&str_2[len_2 - len], str, len);
		}
		else
		{
			str_2 = (char *) malloc (len_2 + 1);
			if (!str_2)
			{
				free(str);
				return (NULL);
			}
			str_2[len_2] = '\0';
			ft_memset(str_2, ' ', len_2);
			ft_memcpy(&str_2[len_2 - len], str, len);
		}
		free(str);
		str = str_2;
		len = len_2;
	}
	return (str);
}

char	*hexa_num_upper(char *s, va_list args)
{
	char	*str;

	//printf("\n__(entra en la funcion hexa_num_upper)__\n");
	str = hexa_num_lower(s, args);
	if (!str)
		return (NULL);
	ft_strtoupper(str);
	return (str);
}

/*FUNCION PARA CREAR EL ARGUENTO A IMPRIMIR*/

char	*create_print_arg(char *s, va_list args)
{
	char	*arg;
	char	c;

	//printf("\n__(entra en la funcion create_print_arg)__\n");
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

char	*create_arg(char *s, va_list args)
{
	char	*str;
	char	*print;
	size_t	len;

	//printf("\n_ (entra en la funcion create_arg)_\n ");
	//printf("\n_ (el string recibido en create_arg es: %s)_\n ", s);
	str = cpy_arg(s);
	if (!str)
		return (NULL);
	//printf("\n_ (el string generado por cpy_arg es: %s)_\n ", str);
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

int	ft_printf(char *s, ...)
{
	va_list	args;
	char	*arg;
	int		printed;
	int		i;

	va_start(args, s);
	printed = 0;
	while (*s)
	{
		if (*s != '%')
		{
			ft_putchar(*s);
			printed++;
			s++;
		}
		else if (s[1] == '%')
		{
			ft_putchar(*s);
			s = s + 2;
			printed++;
		}
		else
		{
			arg = create_arg(s, args);
			if (!arg)
			{
				va_end(args);
				return (-1);
			}
			i = count_arg_len(&s[1]) + 1;
			s = s + i;
			printed = printed + ft_strlen(arg);
			ft_putstr(arg);
			free(arg);
		}
	}
	va_end(args);
	return (printed);
}

int	main()
{
	char			c = 'c';
	char			*s = "Hola mundo";
	void			*p = s;
	int				d = 0;
	unsigned int	u = 123456;
	unsigned int	x = 654321;

	printf("Lo que imprime    printf para c es: %-10c. Esto es para ver si termina donde debe.\n", c);
	ft_printf("Lo que imprime ft_printf para c es: %-10c. Esto es para ver si termina donde debe.\n", c);
	printf("\n");
	printf("Lo que imprime    printf para s es: %-20.5s. Esto es para ver si termina donde debe.\n", s);
	ft_printf("Lo que imprime ft_printf para s es: %-20.5s. Esto es para ver si termina donde debe.\n", s);
	printf("\n");
	printf("Lo que imprime    printf para p es: %-20p. Esto es para ver si termina donde debe.\n", p);
	ft_printf("Lo que imprime ft_printf para p es: %-20p. Esto es para ver si termina donde debe.\n", p);
	printf("\n");
	printf("Lo que imprime    printf para d es: %15.10d. Esto es para ver si termina donde debe.\n", d);
	ft_printf("Lo que imprime ft_printf para d es: %15.10d. Esto es para ver si termina donde debe.\n", d);
	printf("\n");
	printf("Lo que imprime    printf para i es: %+-15.10i. Esto es para ver si termina donde debe.\n", d);
	ft_printf("Lo que imprime ft_printf para i es: %+-15.10i. Esto es para ver si termina donde debe.\n", d);
	printf("\n");
	printf("Lo que imprime    printf para u es: %-20.10u. Esto es para ver si termina donde debe.\n", u);
	ft_printf("Lo que imprime ft_printf para u es: %-20.10u. Esto es para ver si termina donde debe.\n", u);
	printf("\n");
	printf("Lo que imprime    printf para x es: %#20.10x. Esto es para ver si termina donde debe.\n", x);
	ft_printf("Lo que imprime ft_printf para x es: %#20.10x. Esto es para ver si termina donde debe.\n", x);
	printf("\n");
	printf("Lo que imprime    printf para X es: %#X. Esto es para ver si termina donde debe.\n", x);
	ft_printf("Lo que imprime ft_printf para X es: %#X. Esto es para ver si termina donde debe.\n", x);
	printf("\n");
	printf("Lo que imprime    printf para doble porcentaje es: %%. Esto es para ver si termina donde debe.\n");
	ft_printf("Lo que imprime ft_printf para doble porcentaje es: %%. Esto es para ver si termina donde debe.\n");
	printf("Lo que imprime    printf para c es: %c. El segundo argumento d: %d.\n", c, d);
	ft_printf("Lo que imprime ft_printf para c es: %c. El segundo argumento d: %d.\n", c, d);
	return (0);
}
