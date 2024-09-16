/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:21:33 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 11:38:51 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdlib.h>
#include <stdio.h>
*/
int	ft_sqrt(int nb)
{
	int	nb_sqrt;

	nb_sqrt = 1;
	if (nb <= 0)
		return (0);
	while (nb_sqrt * nb_sqrt < nb)
	{
		nb_sqrt++;
	}
	if (nb_sqrt * nb_sqrt == nb)
		return (nb_sqrt);
	else
		return (0);
}
/*
int	main(int argc, char *argv[])
{
	int	n;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	n = ft_sqrt(n);
	printf("El sqrt es %d\n", n);
	return (0);
}
*/
