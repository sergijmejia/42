/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:42:38 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/11 23:36:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

static char	*ft_worddup(const char *start, const char *end)
{
	char	*word;
	size_t	i;

	word = (char *) malloc (end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = *start++;
	word[i] = '\0';
	return (word);
}

static void	ft_findwords(const char *s, char c, char **split)
{
	size_t	i;
	char	*start;

	i = 0;
	start = NULL;
	while (*s)
	{
		if (*s != c && !start)
			start = (char *) s;
		else if ((*s == c || *(s + 1) == '\0') && start)
		{
			if (*s == c)
				split[i++] = ft_worddup(start, s);
			else
				split[i++] = ft_worddup(start, s + 1);
			start = NULL;
		}
		s++;
	}
	if (start)
		split[i++] = ft_worddup(start, s);
	split[i] = NULL;
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	words_s;

	if (s == NULL)
		return (NULL);
	words_s = ft_countwords(s, c);
	split = (char **) malloc ((words_s + 1) * sizeof (char *));
	if (split == NULL)
		return (NULL);
	ft_findwords(s, c, split);
	return (split);
}
/*
int	main(int argc, char *argv[])
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
