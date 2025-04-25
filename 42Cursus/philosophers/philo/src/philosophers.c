/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:39:01 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/25 18:34:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	ft_atoi(char *nptr)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	if (!nptr)
		return (0);
	while (*nptr && ((*nptr >= '\t' && *nptr <= '\r') || (*nptr == ' ')))
		nptr++;
	if (*nptr == '-')
		negative = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	return (res * negative);
}

int	check_values(int argc, char **argv)
{
	int	arg1;
	int	arg2;
	int	arg3;
	int arg4;
	int	arg5;

	arg1 = ft_atoi(argv[1]);
	arg2 = ft_atoi(argv[2]);
	arg3 = ft_atoi(argv[3]);
	arg4 = ft_atoi(argv[4]);
	if (arg1 <= 0 || arg2 <= 0 || arg3 <= 0 || arg4 <= 0)
		return (1);
	if (argc == 6)
	{
		arg5 = ft_atoi(argv[5]);
		if (arg5 <= 0)
			return (1);
	}
	return (0);
}

void	philosophers(t_philo_data philo)
{
	t_philo	*philosophers;

	philosophers = (t_philo *) malloc (sizeof t_philo * philo->number_of_philo);
}

void	complete_philo_data(int argc, void **argv, t_philo_data *philo)
{
	philo->number_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->number_to_eat = ft_atoi(argv[5]);
	else
		philo->number_to_eat = -1;
}

int	main(int argc, char **argv)
{
	int	number_to_eat;
	philo_data_t philo;

	printf("La cantidad de argumentos es: %d\n", argc);
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments.\n", 27);
		exit(EXIT_FAILURE);
	}
	if (check_values(argc, argv))
	{
		write(2, "Negative or nul arguments.\n", 27);
		exit(EXIT_FAILURE);
	}
	complete_philo_data(argc, argv, &philo);
	philosophers(philo);
	return (EXIT_SUCCESS);
}
