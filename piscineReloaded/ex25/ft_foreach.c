/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:43:44 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/17 20:04:12 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>

void	ft_print_number(int num)
{
	printf("%d\n", num);
	return ;
}
*/
void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	i;

	i = 0;
	while (i < length)
	{
		f(*tab);
		tab++;
		i++;
	}
	return ;
}
/*
int	main(int argc, char *argv[])
{
	int	*num;
	int	*aux;

	if (argc != 5)
		return (1);
	num = (int *) malloc (sizeof(int) * 4);
	aux = num;
	*aux = atoi(argv[1]);
	aux++;
	*aux = atoi(argv[2]);
	aux++;
	*aux = atoi(argv[3]);
	aux++;
	*aux = atoi(argv[4]);
	ft_foreach(num, 4, &ft_print_number);
	return (0);
}
*/
