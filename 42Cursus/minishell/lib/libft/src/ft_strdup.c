/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:26:24 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/02 13:18:24 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <string.h>*/

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	len = ft_strlcpy(str, s, len + 1);
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	char	*new_str;
	char	*new_strft;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	new_strft = ft_strdup(argv[1]);
	if (new_strft == NULL)
	{
		printf("Error al dupllicar la cadena\n");
		return (1);
	}
	new_str = strdup(argv[1]);
	if (new_str == NULL)
	{
		printf("Error al dupllicar la cadena\n");
		return (1);
	}
	printf("El nuevo string con la funcion ft es %s\n", new_strft);
	printf("El nuevo string con la cuncion s es %s\n", new_str);
	free(new_strft);
	free(new_str);
	return (0);
}
*/
