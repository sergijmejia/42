#include "ft_printf.h"

int	ft_create_character_arg(const char *s, va_list args, char **arg)
{
	char	*str;
	size_t	min_field;
	int		len;
	
	str = (char *) s;
	min_field = ft_cal_min_field(str);
	if (ft_flag(str, '-') && (min_field > 1))
		len = (int) min_field;
	else
		len = 1;
	*arg = (char *) malloc (len + 1);
	if (!*arg)
		return (-1);
	ft_memset(*arg, ' ', len);
	(*arg)[0] = (char) va_arg(args, int);
	(*arg)[len] = '\0';
	return (len);
}
