/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:29:30 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/11 16:40:00 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	str_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t) start >= s_len)
		return (ft_strdup(""));
	if ((s_len - (size_t) start) < len)
		str_len = s_len - (size_t) start;
	else
		str_len = len;
	str = (char *) malloc (str_len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, str_len + 1);
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
