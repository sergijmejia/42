/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:30:42 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/11 17:34:55 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;

	little_len = ft_strlen(little);
	if ((big == NULL) || (little_len > len))
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && (i + little_len <= len))
	{
		if (ft_strncmp(&big[i], little, little_len) == 0)
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(int argc, char *argv[])
{
	char	*res;
	int		c;

	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s <str1> <str2> [<len>]\n", argv[0]);
		return (1);
	}
	else
	{
		c = atoi(argv[3]);
		res = ft_strnstr(argv[1], argv[2], c);
	}
	if (res == NULL)
	{
		printf("No se ha encontrado <str2> en <str1>");
		printf("\n");
	}
	else
		printf("Encontrado. El string a partir de ese punto es: %s\n", res);
	return (0);
}
*/
