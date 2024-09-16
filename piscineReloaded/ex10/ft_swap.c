/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:45:20 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 09:59:52 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <stdlib.h>
*/
void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}
/*
int	main(int argc, char *argv[])
{
	int	x;
	int	y;
	int	*px;
	int	*py;
	
	if (argc != 3)
		return (1);
	px = &x;
	py = &y;
	x = atoi(argv[1]);
	y = atoi(argv[2]);
	printf("El valor original de x es %d\n", x);
	printf("El valor original de y es %d\n", y);
	ft_swap(px, py);
	printf("El nuevo valor de x es %d\n", x);
	printf("El nuevo valor de y es %d\n", y);
	return (0);
}
*/
