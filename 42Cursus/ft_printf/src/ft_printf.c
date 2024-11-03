/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:01:01 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/02 14:59:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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
/*
int	main()
{
	char			c = 'c';
	char			*s = "Hola mundo";
	void			*p = s;
	int				d = 0;
	unsigned int	u = 123456;
	unsigned int	x = 654321;
	int				printed_printf;
	int				printed_ft_printf;

	printed_printf = printf("Lo que imprime    printf para c es: %-10c.", c);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para c es: %-10c.", c);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para s es: %-20.5s.", s);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para s es: %-20.5s.", s);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para p es: %-20p.", p);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para p es: %-20p.", p);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para d es: %15.10d.", d);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para d es: %15.10d.", d);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para i es: %+-15.10i.", d);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para i es: %+-15.10i.", d);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para u es: %-20.10u.", u);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para u es: %-20.10u.", u);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para x es: %#20.10x.", x);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para x es: %#20.10x.", x);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para X es: %#X.", x);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para X es: %#X.", x);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para doble porcentaje es: %%.");
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para doble porcentaje es: %%.");
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Lo que imprime    printf para c es: %c. El segundo argumento d: %d.", c, d);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Lo que imprime ft_printf para c es: %c. El segundo argumento d: %d.", c, d);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	return (0);
}
*/
