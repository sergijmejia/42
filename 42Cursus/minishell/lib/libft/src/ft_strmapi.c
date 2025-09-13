/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:03:56 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/05 00:47:29 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>

static char	prueba(unsigned int i, char c)
{
	(void)i;
	return (ft_toupper(c));
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	str = (char *) malloc (ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	char	*str;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	printf("El string orignal es: %s\n", argv[1]);
	str = ft_strmapi(argv[1], prueba);
	printf("El string despues de ft_strmapi es: %s\n", str);
	free (str);
	return (0);
}
*/
