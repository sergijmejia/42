/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:15:35 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/06 13:43:34 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_num_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments.\n", 27);
		return (1);
	}
	return (0);
}

static int	check_numerical_arg(char *str)
{
	if (str_is_num(str))
	{
		write(2, "No numeric arguments not allowed.\n", 34);
		return (1);
	}
	return (0);
}

static int	check_neg_num(long long num)
{
	if (num > INT_MAX || num < INT_MIN)
	{
		write(2, "The arguments must be in the integer range.\n", 44);
		return (1);
	}
	if (num < 0)
	{
		write(2, "Negative arguments not allowed.\n", 32);
		return (1);
	}
	if (num == 0)
	{
		write(2, "Null arguments not allowed.\n", 28);
		return (1);
	}
	return (0);
}

int	check_values(int argc, char **argv)
{
	long long	arg[5];
	int			i;

	if (check_num_args(argc))
		return (1);
	i = 0;
	while (i < 4)
	{
		if (check_numerical_arg(argv[i + 1]))
			return (1);
		arg[i] = ft_atoll(argv[i + 1]);
		if (check_neg_num(arg[i]))
			return (1);
		i++;
	}
	if (argc == 6)
	{
		if (check_numerical_arg(argv[5]))
			return (1);
		arg[4] = ft_atoll(argv[5]);
		if (check_neg_num(arg[4]))
			return (1);
	}
	return (0);
}
