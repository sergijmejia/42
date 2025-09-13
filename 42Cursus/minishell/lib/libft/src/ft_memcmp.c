/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:29:23 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/14 19:23:54 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	int				num;

	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	num = 0;
	while (num < ((int) n))
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
		num++;
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
