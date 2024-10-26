/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:39:12 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/21 18:17:44 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft.h"

int	ft_intlen(int n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

char	*unsig_int(unsigned int num)
{
	int		len;
	int		aux;
	char	*str;

	len = 0; 
	if (n == 0)
		return (1);
	aux = num;
        while (aux != 0)
        {
                aux = aux / 10;
                len++;
        }
	str = (char *) malloc (len +1);
	if (!str)
		return (NULL);
	str[len] ='\0';
	while (num != 0)
	{
		str[len - 1] = '0' + num % 10;
		num = num / 10;
		len--;
	}
	return (str);
}

char	*hexa_num(int num)
{
	char	*str;
	int		len;
	int		aux;

	aux = num;
	len = ft_intlen(num, 16);
	str = (char) malloc (len + 1);
	if (num < 0)
	{
		num = -num;
		str[0] = '-';
	}
	base = {"0123456789abcdef"};
	str[len] = '\0'; 
	while (num != 0)
	{
		str[len - 1] = base[num % 16];
		len--;
		num = num / 16;
	}
	return (str);
}

char	*hexa_pointer(void* arg)
{
	int		len;
	int		n;

	n = (int) arg;
	return (hexa_num(n));
}




























char	*check_arg(char *s, va_list args, int precision, int *field, char *str)
{
	if(*s == 'c')
		str = arg_char(args, precision);
	if(*s == 's')
		str = arg_str(args, precision);
	if(*s == 'p')
		str = arg_pnt_hexa(args, precision);
	if(*s == 'd')
		str = arg_dec_b10(args, precision);
	if(*s == 'i')
		str = arg_int_b10(args, precision);
	if(*s == 'u')
		str = arg_dec_ns(args, precision);
	if(*s == 'x')
		str = arg_hexa(args, precision);
	if(*s == 'X')
		str = arg_hexa_caps(args, precision);
	if (*s == '%')
		*str = '%'
	return (str);
}

int     check_field_min(char *s)

{
	int	min_field;

	min_field = 0;
	while (ft_isdigit(*s))
	{
		min_field = 10 * min_field + ft_atoi(*s);
		s++;
	}
	return (min_field);
}



int	cal_field_min(char *s)

{
	int		min_field;
	char    *str_field;
	char	*aux;

	min_field = 0;
	while (ft_isdigit(*s))
	{
		min_field = 10 * min_field + ft_atoi(*s);
		s++;
	}
	s = s + ft_intlen(min_field);
	str = possible_arg(s, args, precision, str);
	if (min_fiield > ft_strlen(str))
	{
		str_field = (char *) malloc (min_field + 1);
		str_field = memset(str_field, ' ', min_field);
		str_field[min_field] = '\0';
		aux = str_field[min_field - ft_strlen(str)];
                ft_memcpy(aux, str, ft_strlen(str));
                free(str);
	}

	return (i);
}

char	*flag_minus(char *s, va_list args, int precision, , int *field, char *str)
{
	char	*str_flag;
	int	zero;
	int	plus;
	int
	s++;
	field_min = check_field_min(s);
	if (field_min)
		s = s + ft_intlen(field_min);
	possible_arg(s, args, precision, str);
	if (ft_strlen(str) < field_min)
	{
		str_flag = (char *) malloc (field_min + 1);
		if (str_fag == NULL)
			return (NULL);
		str_flag = memset(str_flag, ' ', field_min);
		str_flag[field_min] = '\0';
		ft_memcpy(str_flag, str, ft_strlen(str));
		free(str);
		return (str_flag);
	}
	else
		return (str);
}

void	find(int *minus, int *zero, int *hash, int *space, int *plus, char *s)
{
	while (ft_contains("-0# +", s))
	{
		if (*s == '-')
			*minus = 1;
		if (*s == '0')
			*zero = 1;
		if (*s == '#')
			*hash = 1;
		if (*s == ' ')
			*space = 1;
		if (*s == '+')
			*plus = 1;
		s++;
	}
}

char	*check_precision(char *s, va_list args, int precision, int *field, char *str)
{
	s++;
	precision = 0;
	while (ft_isdigit(*s))
	{
		precision = 10 * precision + ft_atoi(*s);
		s++;
	}
	possible_arg(s, args, precision, field, str);
	return (str);
}


int	check_flags(char *s, va_list args, int precision, int *field, char *str)
{
	
	
	
	int	minus;
	int	zero;
	int	hash;
	int	space;
	int	plus;
	int	field_min;

	minus = 0;
	zero = 0;
	hash = 0;
	space = 0;
	plus = 0;
	find(&minus, &zero, &hash, &space, &plus, s);
	s = s + minus + zero + hash + space + plus;
	if (*s == '.' || minus)
		zero = 0;
	if (plus)
		space = 0;
	str = possible_arg(s, args, precision, field, str);
	if (


}






	int		i;
	int		field_min;
	char	*str_flag;
	char	*aux;

	field_min = 0;

	if(*s == '-')
	{
		s++;
		field_min = check_field_min(s);
		if (field_min)
			s = s + ft_intlen(field_min);
		possible_arg(s, args, precision, str);
		if (ft_strlen(str) < field_min)
		{
			str_flag = (char *) malloc (field_min + 1);
			if (str_fag == NULL)
				return (NULL);
			str_flag = memset(str_flag, ' ', field_min);
			str_flag[field_min] = '\0';
			ft_memcpy(str_flag, str, ft_strlen(str));
			free(str);
			return (str_flag);
		}
		else
			return (str);
	}

	if (*s == '.')
	{
		s++;
		precision = 0;
		while (ft_isdigit(*s))
		{
			precision = 10 * precision + ft_atoi(*s);
			s++;
		}
		possible_arg(s, args, precision, str);
		return (str);
	}



	if(*s == '0')
	{
		s++;
		field_min = check_field_min(s);
		if (field_min)
			s = s + ft_intlen(field_min);
		possible_arg(s, args, precision, str);
		if (ft_strlen(str) < field_min)
		{
			str_flag = (char *) malloc (field_min + 1);
			if (str_fag == NULL)
				return (NULL);
			str_flag = memset(str_flag, '0', field_min);
			str_flag[field_min] = '\0';
			i = field_min - ft_strlen(str);
			ft_memcpy(&str_flag[i], str, ft_strlen(str));
			free(str);
			return (str_flag);
		}
		else
			return (str);
	}

	if(*s == '#')
        {
                s++;
                field_min = check_field_min(s);
                if (field_min)
                        s = s + ft_intlen(field_min);
                possible_arg(s, args, precision, str);
                if (ft_strlen(str) + 2 < field_min)
                {
                        aux = &(s - 1);
			if ((aux == 'x') || (aux == 'X'))
			{
				str_flag = (char *) malloc (field_min + 3);
				if (str_fag == NULL)
					return (NULL);
				str_flag[0] = '0';
				str_flag[1] = *aux;
			}
                        str_flag[0] = 0;
			str_flag[1] = *aux;
                        str_flag[field_min + 2] = '\0';
                        ft_memcpy(str_flag, str, ft_strlen(str));
                        free(str);
                        return (str_flag);
                }
                else

                        return (str);
        }



}


char	*possible_arg(const char *s, va_list args, int precision, int *field, char *str)
{
	int	min_field;

	if (ft_contains("-0# +", *s))
		check_flags(s, args, precision, field, str);
	else if (*s == '.')
		check_precision(s, args, precision, field, str);
	else if (ft_contains("123456789", s))
	{
		*field = cal_field_min(s);
		possible_arg(s, args, precision, field, str);
	}
	else if(ft_contains("cspdiuxX%", *s))
		check_arg(*s, args, precision, field, str);
	else
	{
		str = '%';
		*progress = 1;
	}
	return (str);
}

int	ft_printf(char *s, ...)
{
	va_list	args;
	char	str;
	int		*i;
	int		precision;

	i = 0;
	precision = -1;
	va_start(args, s);
	while (*s)
	{
		str = NULL;
		if (*s == '%')
		{
			s = possible_arg(s, args, precision, str);
			i = i + ft_strlen(str);
			ft_putstr(str);
			free(str);
		}
		else
		{
			ft_putchar(*s);
			i++;
			s++;
		}
	}
	va_ends(args);
	return (i);
}

