/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:34:47 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/28 13:55:50 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/*#include <stdio.h>
#include "libft.h"*/

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int	num;

	num = 0;
	while (num < ((int) n))
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
			num++;
		}
		else
		{
			return (*s1 - *s2);
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
