/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:42:38 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/14 19:39:44 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

static char	**free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**create_split(char const *s, char **split, char c)
{
	char	*start;
	int		num;

	num = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = (char *)s;
			while (*s && (*s != c))
				s++;
			split[num] = ft_substr(start, 0, s - start);
			if (split[num] == NULL)
				return (free_split(split));
			num++;
		}
	}
	split[num] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = ft_calloc(ft_countwords(s, c) + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	return (create_split(s, split, c));
}
/*
//int	main(int argc, char *argv[])
int	main(void)
{
	char	**str;
	size_t	num;

	if (argc != 3)
	{
		printf("La cantidad de argumentos es incorrecta.\n");
		return (1);
	}
	if (strlen(argv[2]) > 1)
	{
		printf("Cantidad de caracteres incorrecta\n");
		return (1);
	}
	str = ft_split(argv[1], *argv[2]);
	//str = ft_split("hello!", ' ');
	num = 0;
	printf("La funcion ft_split divide en varios strings:\n");
	while (str[num])
	{
		printf("%s\n", str[num]);
		num++;
	}
	while (num > 0)
	{
		free(str[num - 1]);
		num--;
	}
	free(str);
	return (0);
}
*/
