/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:34:47 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 13:55:50 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	n;

	n = 0;
	while ((*s1 == *s2) && (*s1 != '\0'))
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
	{
		n = *s1 - *s2;
		return (n);
	}
}
/*
int	main(int argc, char *argv[])
{
	int	res;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <str1> <str2> [<len>]\n", argv[0]);
		return (1);
	}
	else
		res = ft_strcmp(argv[1], argv[2]);
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
