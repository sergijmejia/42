#include <stdlib.h>
#include <string.h>
//#include <stdio.h>

//Tengo que incluir la funcion ft_strlen. Para hacer las pruebas lo voy a hacer con la funcion strlen
//tengo qu eincluir la funcion ft_putstr. Para hacer las pruebas lo voy a hacer con la funcion puts
//int	ft_strlen(char *str)
//void	ft_putstr(char *str)


char	*ft_strdup(char *src)
{
	char	*new_pointer;
	char	*aux_pointer;

	new_pointer = (char *) malloc ((strlen(src) + 1) * sizeof(char));
	aux_pointer = new_pointer;
	while (*src != '\0')
	{
		*aux_pointer = *src;
		aux_pointer++;
		src++;
	}
	*aux_pointer = '\0';
	return (new_pointer);
}
/*
int	main(int argc, char *argv[])
{
	char	*new_string;

	if (argc != 2)
		return (1);
	new_string = ft_strdup(argv[1]);
	puts(new_string);
	return (0);
}
*/
