/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:07 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/11 18:59:18 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		str = ft_strdup(s2);
	if (s2 == NULL)
		str = ft_strdup(s1);
	if (s1 != NULL && s2 != NULL)
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		str = (char *) malloc (len_s1 + len_s2 + 1);
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, s1, len_s1 + len_s2 + 1);
		ft_strlcat(str, s2, len_s1 + len_s2 + 1);
	}
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	char	*str;

	if (argc != 3)
	{
		printf("La cantidad de argumentos es incorrecta\n");
			return (1);
	}
	str =  ft_strjoin(argv[1], argv[2]);
	if (str == NULL)
	{
	printf("Error en la asignacion de memoria\n");
	return (1);
	}
	printf("El nuevo string es: %s\n", str);
	free(str);
	return (0);
}
*/
