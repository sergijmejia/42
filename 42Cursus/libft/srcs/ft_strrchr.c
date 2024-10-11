/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:54:12 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/11 15:44:10 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	chr;
	const char		*str;
	int				pos;	

	if (s == NULL)
		return (NULL);
	str = NULL;
	chr = (unsigned char) c;
	pos = ft_strlen(s);
	while (pos >= 0)
	{
		if (s[pos] == chr)
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
