/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:16:21 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 13:23:15 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdlib.h>
#include <stdio.h>
*/
int	ft_recursive_factorial(int nb)
{
	int	fact;

	if (nb == 0)
		return (1);
	if ((nb < 0) || (nb > 12))
		return (0);
	fact = 1;
	if (nb != 1)
		fact = ft_recursive_factorial(nb -1);
	fact = fact * nb;
	return (fact);
}
/*
int	main(int argc, char *argv[])
{
	int	n;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	n = ft_recursive_factorial(n);
	printf("El factorial es %d\n", n);
	return (0);
}
*/
