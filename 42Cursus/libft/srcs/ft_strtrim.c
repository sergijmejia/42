/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:27:02 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/03 11:53:30 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	end = ft_strlen(s1);
	start = 0;
	while (start < end)
	{
		if (!ft_strcontains(set, s1[start]))
		{
			s1 = &s1[start];
			break ;
		}
		start++;
	}
	end = end - start;
	while (end > start)
	{
		if (!ft_strcontains(set, s1[end - 1]))
			break ;
		end--;
	}
	str = (char *) malloc (end + 1);
	start = ft_strlcpy(str, s1, end + 1);
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	char	*str;
	size_t	num;

	if (argc != 3)
	{
		printf("La cantidad de argumentos es incorrecta.\n");
		return (1);
	}
	num = ft_strlen(argv[2]);
	str = ft_strtrim(argv[1], argv[2]);
	printf("El string despues de ft_strtrim es: %s\n", str);
	free(str);
	return (0);
}
*/
