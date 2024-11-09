

int	ft_strcontains(const char *str, char c)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

