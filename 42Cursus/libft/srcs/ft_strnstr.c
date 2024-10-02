/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:30:42 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/02 01:16:59 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	char	*l;
	size_t	n;
	int		comp;

	if (big == NULL)
		return (NULL);
	if (little == NULL)
		return ((char *)big);
	b = (char *) big;
	l = (char *) little;
	n = 0;
	comp = 1;
	while ((n + ft_strlen(l) <= len) && (n + ft_strlen(l) < ft_strlen(big)))
	{
		if (*b == *l)
		{
			comp = ft_strncmp(b, l, ft_strlen(l));
			if (comp == 0)
				return (b);
		}
		b++;
		n++;
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
