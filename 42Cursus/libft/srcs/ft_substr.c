/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:29:30 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/09 14:20:58 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = (char *) malloc (len);
	if (str == NULL)
		return (NULL);
	if ((size_t) start > ft_strlen(s))
		return (str);
	s = &s[start];
	ft_strlcpy(str, s, len);
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	char	*new_strft;
	int		n_ft;

	if (argc != 3)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	n_ft = ft_atoi(argv[2]);
	new_strft = ft_substr(argv[1], n_ft, 20);
	printf("El nuevo string con la funcion ft es %s\n", new_strft);
	free(new_strft);
	return (0);
}
*/
