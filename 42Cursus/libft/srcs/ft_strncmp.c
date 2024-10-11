/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:34:47 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/11 17:39:25 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			num;
	unsigned char	c_s1;
	unsigned char	c_s2;

	num = 0;
	while (num < n)
	{
		c_s1 = (unsigned char) *s1;
		c_s2 = (unsigned char) *s2;
		if (c_s1 == c_s2)
		{
			if (c_s1 == '\0')
				return (0);
			s1++;
			s2++;
			num++;
		}
		else
		{
			return (c_s1 - c_s2);
		}
	}
	return (0);
}
/*
int	main(int argc, char *argv[])
{
	int	res;
	int	c;

	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s <str1> <str2> [<len>]\n", argv[0]);
		return (1);
	}
	else
	{
		c = atoi(argv[3]);
		res = ft_strncmp(argv[1], argv[2], c);
	}
	if (res == 0)
	{
		printf("<str1> and <str2> are equal");
		printf("\n");
	}
	else if (res < 0)
		printf("<str1> is less than <str2> (%d)\n", res);
	else
		printf("<str1> is greater than <str2> (%d)\n", res);
	return (0);
}
*/
