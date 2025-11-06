/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:06:26 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/06 14:27:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	complete_data(int argc, char **argv,
				t_philo_data **d, long long start_time)
{
	(*d)->num_philo = ft_atoi(argv[1]);
	(*d)->time_to_die = ft_atoi(argv[2]);
	(*d)->time_to_eat = ft_atoi(argv[3]);
	(*d)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*d)->number_to_eat = ft_atoi(argv[5]);
	else
		(*d)->number_to_eat = -1;
	(*d)->time_start = start_time;
	(*d)->finished = 0;
	return ;
}

static void	complete_philosophers(t_philo_data **d)
{
	int	i;

	i = 0;
	while (i < (*d)->num_philo)
	{
		pthread_mutex_init(&((*d)->forks[i]), NULL);
		(*d)->philosophers[i].r_fork = i + 1;
		(*d)->philosophers[i].l_fork = i;
		(*d)->philosophers[i].id = i + 1;
		(*d)->philosophers[i].data = (*d);
		(*d)->available_forks[i] = 1;
		i++;
	}
	return ;
}

t_philo_data	**complete_philo_data(int argc, char **argv,
					t_philo_data **d, long long start_time)
{
	complete_data(argc, argv, d, start_time);
	(*d)->available_forks = (int *) malloc (sizeof(int) * ((*d)->num_philo));
	if (!((*d)->available_forks))
		return (NULL);
	(*d)->forks = (pthread_mutex_t *) malloc
		(sizeof(pthread_mutex_t) * ((*d)->num_philo));
	if (!((*d)->forks))
	{
		free((*d)->available_forks);
		return (NULL);
	}
	(*d)->philosophers = (t_philo *) malloc
		(sizeof(t_philo) * ((*d)->num_philo));
	if (!((*d)->philosophers))
	{
		free((*d)->available_forks);
		free((*d)->forks);
		return (NULL);
	}
	complete_philosophers(d);
	(*d)->philosophers[0].l_fork = (*d)->num_philo;
	pthread_mutex_init(&((*d)->read_forks), NULL);
	pthread_mutex_init(&((*d)->msg), NULL);
	pthread_mutex_init(&((*d)->sim), NULL);
	return (d);
}
