

#include <stddef.h>
#include "libft.h"
/*#include <string.h>
#include <stdio.h>*/

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;
	int			pos;	

	if ((s == NULL) || (!ft_isascii(c)))
		return (NULL);
	str = NULL;
	pos = ft_strlen(s);
	while (pos >= 0)
	{
		if (s[pos] == c)
		{
			str = &s[pos];
			break ;
		}
		pos--;
	}
	return ((char *) str);
}
/*
int	main(int argc, char *argv[])
{
	char	*src;
	char	*src_ft;
	//char	*src_null;
	char	c;
	int		num;

	if (argc != 3)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	//src_null = NULL;
	num = atoi(argv[2]);
	src = strrchr(argv[1], num);
	src_ft = ft_strrchr(argv[1], num);
	c = (char) num;
	printf("El ascii buscado es %c\n", c);
	if (src == NULL)
		printf("strrchr no encontro el caracter ascii %d\n", num);
	else
		printf("El string desde strrchr es: %s\n", src);
	if (src_ft == NULL)
		printf("ft_strrchr no encontro el caracter ascii %d\n", num);
	else
		printf("El string desde ft_strrchr es: %s\n", src_ft);
	return (0);
}
*/
