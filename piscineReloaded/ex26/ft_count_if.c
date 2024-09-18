/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:13:35 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/18 13:27:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_contains_a(char *tab)
{
	while (*tab != '\0')
	{
		if (*tab == 'a' || *tab == 'A')
			return (1);
		tab++;
	}
	return (0);
}

int	ft_count_if(char **tab, int (*f)(char*))
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (tab[i] != NULL)
	{
		if (f(tab[i]) == 1)
			count++;
		i++;
	}
	return (count);
}
/*
int	main(int argc, char *argv[])
{
	int	count;

	if (argc < 2)
		return (1);
	count = ft_count_if(argv, &ft_contains_a);
	printf("Hay %d elementos que contiene la letra a.\n", count);
	return (0);
}
*/
