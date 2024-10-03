/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:42:38 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/03 16:16:54 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	**ft_split(const char *s, char c)
{
	size_t	aux;
	size_t	i;
	char	**split;

	if (s == NULL)
		return (NULL);
	split = (char **) malloc ((ft_countchar(s, c) + 2) * sizeof (char *));
	i = 0;
	aux = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			split[aux] = (char *) malloc (i + 1);
			ft_strlcpy (split[aux], s, i +1);
			s = &s[i + 1];
			i = 0;
			aux++;
		}
		else
			i++;
	}
	split[aux] = (char *) malloc (i + 1);
	ft_strlcpy (split[aux], s, i +1);
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
	if (ft_strlen(argv[2]) > 1)
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
