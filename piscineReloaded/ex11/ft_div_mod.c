/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:01:50 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 10:14:05 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <stdlib.h>
*/
void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a / b;
	*mod = a % b;
}
/*
int	main(int argc, char *argv[])
{
	int	x;
	int	y;
	int	d;
	int	m;
	int	*div;
	int	*mod;

	if (argc != 3)
		return (1);
	div = &d;
	mod = &m;
	x = atoi(argv[1]);
	y = atoi(argv[2]);
	ft_div_mod(x, y, div, mod);
	printf("El valor de la division es %d\n", d);
	printf("El valod delm modulo es %d\n", m);
	return (0);
}
*/
