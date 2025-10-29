/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:04:02 by smejia-a          #+#    #+#             */
/*   Updated: 2025/05/05 19:11:26 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	complete_philo_data(int argc, char **argv, t_philo_data *philo)
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

static void	philosophers_start(t_philo *philosophers, t_philo_data philo, pthread_mutex_t *forks, t_waiter *waiter, pthread_mutex_t *stdout_mutex)
{
	int				i;
	long long		first_think;
	struct timeval	actual_tv;

	i = 0;
	while (i < 2)
	{
		//printf("Se crea el filosofo numero %d\n", i + 1);
		philosophers[i].id = i + 1;
		gettimeofday(&actual_tv, NULL);
		first_think = actual_tv.tv_sec * 1000 + actual_tv.tv_usec / 1000;
		//printf("el tiempo para empezar a pensar es: %lld\n", first_think);
		philosophers[i].data = philo;
		philosophers[i].time_last_eat = first_think;
		philosophers[i].left_fork = &forks[i];
		if (i == (philo.number_of_philo - 1))
			philosophers[i].right_fork = &forks[0];
		else
			philosophers[i].right_fork = &forks[i + 1];
		philosophers[i].state = 0;
		philosophers[i].is_alive = 1;
		philosophers[i].waiter = waiter;
		philosophers[i].stdout_mutex = stdout_mutex;
		pthread_create(&philosophers[i].thread, NULL, routine, &philosophers[i]);
		i++;
	}
}

int 	main()
	int	main(int argc, char **argv)
{
	t_philo_data philo;
	t_philo	*philosophers;
	pthread_mutex_t *forks;
	pthread_mutex_t stdout_mutex;
	t_waiter	waiter;
	int	n;

	//printf("La cantidad de argumentos es: %d\n", argc);
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
	n = philo.number_of_philo;
	philosophers = (t_philo *) malloc (sizeof (t_philo) * n);
	forks = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t) * n);
	forks_start(forks, n);
	waiter.id_next_eat = 1;
	philosophers_start(philosophers, philo, forks, &waiter, &stdout_mutex);
	return (EXIT_SUCCESS);
}
