/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:25 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/16 16:47:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//#include <stdio.h>

int	*ft_range(int min, int max)
{
	int	*range;
	int	*aux;

	if (min >= max)
		return (NULL);
	range = (int *) malloc ((max - min + 1) * sizeof(int));
	aux = range;
	while (min < max)
	{
		*aux = min;
		min++;
		aux++;
	}
	*aux = '\0';
	return (range);
}
/*
void	ft_print_numbers(int *num)
{
	while (*num != '\0')
	{
		printf("%d ", *num);
		num++;
	}
	printf("\n");
}

int	main(int argc, char *argv[])
{
	int	min;
	int	max;
	int	*range;
	
	if (argc != 3)
		return (1);
	min = atoi(argv[1]);
	max = atoi(argv[2]);
	range = ft_range(min, max);
	ft_print_numbers(range);
}
*/
