/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:50:09 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/26 15:29:38 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	cout_arg_len(char *s)
{
	size_t	len;

	len = 0;
	while (*aux && ft_strcontains("-0.# +123456789", *aux))
	{
		len++;
		s++;
	}
	if (*aux && ft_strcontains("cspdiuxX", *aux))
	{
		len++;
		aux++;
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

char	*hexa_num(va_list args)
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

char	*arg_to_str(char c, va_list args)
{
	char	*arg;
	void	*pnt;
	
	if (c == 'c')
	{
		arg = (char *) malloc (2);
		arg [0] = (char) va_arg(args, int);
		arg[1] = '\0';
	}
	if (c == 's')
		arg = va_arg(args, char *);
	if (c == 'p')
		arg = hexa_pointer(args);
	if (c == 'd'|| c == 'i')
		arg = ft_itoa(va_arg(args, int));
	if (c == 'u')
		arg = unsig_int(args);
	if (x == 'x')
		arg = hexa_num(args);
	if (x == 'X')
	{
		arg = hexa_num(args);
		ft_strtoupper(arg);
	}
	return (arg);
}

char	*create_print_arg(char *s, va_list args)
{
	size_t	i;
	char	*arg;

	i = ft_strlen(s);
	arg = arg_to_str(s[i], args);

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


