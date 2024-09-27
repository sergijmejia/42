/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:29:40 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/27 20:08:07 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
/*#include <string.h>
#include <stdio.h>*/

char	*ft_strchr(const char *s, int c)
{
	const char	*str;

	if ((s == NULL) || (!ft_isascii(c)))
		return (NULL);
	str = NULL;
	while (*s != '\0')
	{
		if (*s == c)
		{
			str = s;
			break ;
		}
		s++;
	}
	if (c == '\0')
		str = s;
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
	src = strchr(argv[1], num);
	src_ft = ft_strchr(argv[1], num);
	c = (char) num;
	printf("El ascii buscado es %c\n", c);
	if (src == NULL)
		printf("strchr no encontro el caracter ascii %d\n", num);
	else
		printf("El string desde strchr es: %s\n", src);
	if (src_ft == NULL)
		printf("ft_strchr no encontro el caracter ascii %d\n", num);
	else
		printf("El string desde ft_strchr es: %s\n", src_ft);
	return (0);
}
*/
