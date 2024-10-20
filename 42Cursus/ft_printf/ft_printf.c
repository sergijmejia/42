int	select_arg(char *s, va_list args, *progress) //mejor deberia devolver un string para poder adaptarlo a las flags
{
	int	printed;

	if(*s == 'c')
		printed = arg_char(args, progress);
	if(*s == 's')
		printed = arg_str(args, progress);
	if(*s == 'p')
		printed = arg_pnt_hexa(args, progress);
	if(*s == 'd')
		printed = arg_dec_b10(args, progress);
	if(*s == 'i')
		printed = arg_int_b10(args, progress);
	if(*s == 'u')
		printed = arg_dec_ns(args, progress);
	if(*s == 'x')
		printed = arg_hexa(args, progress);
	if(*s == 'X')
		printed = arg_hexa_caps(args, progress);
	if (*s == '%')
	{
		putchar('%');
		*progress++;
		printed = 1;
	}
	return (printed);	
}

int	check_flags(char *s, int progress)
{

}


int	possible_arg(char *s, va_list args, int *progress)
{
	char	*str;

	str = s;
	str++;
	if (ft_contains("-0.# +", str))
	{
		printed = //busca flags
	}
	else if(ft_contains("cspdiuxX%", str))
	{
		printed = select_arg(*str, args, progress);
		return (printed);
	}
	else 
	{
		putchar('%');
		*progress = 1;
		return (1);
	}
}

int	ft_printf(char *s, ...)
{
	va_list	args;
	int		*i;
	int		*progress;

	progress = (int *) malloc (sizeof int);
	i = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			i = i + possible_arg(s, args, progress);
			s = s + *progress;
		}
		else
		{
			ft_putchar(*s);
			i++;
			s++;
		}
	}
	va_ends(args);
	free (progress);
	return (i);
}
