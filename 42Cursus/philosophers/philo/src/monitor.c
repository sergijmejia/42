/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:17:31 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/06 10:21:05 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_eat_all(t_philo_data *philo)
{
	int	num_to_eat;
	int	n_philo;
	int	i;

	num_to_eat = philo->number_to_eat;
	n_philo = philo->num_philo;
	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_lock(&(philo->philosophers[i].philo_mutex));
		if (philo->philosophers[i].num_eat < num_to_eat)
		{
			pthread_mutex_unlock(&(philo->philosophers[i].philo_mutex));
			return (0);
		}
		pthread_mutex_unlock(&(philo->philosophers[i].philo_mutex));
		i++;
	}
	return (1);
}

static int	monitor_loop(t_philo_data *philo, int pos)
{
	t_philo		*philosopher;

	if ((philo->number_to_eat != -1) && (check_eat_all(philo)))
	{
		pthread_mutex_lock(&(philo->sim));
		philo->finished = 1;
		pthread_mutex_unlock(&(philo->sim));
		return (1);
	}
	philosopher = &(philo->philosophers[pos]);
	if (monitorize_finished(philosopher))
		return (1);
	if (check_alive(philosopher) == -1)
	{
		pthread_mutex_lock(&(philo->sim));
		philo->finished = 1;
		pthread_mutex_unlock(&(philo->sim));
		return (1);
	}
	return (0);
}

void	monitor(t_philo_data *philo)
{
	int			n_philo;
	int			i;

	n_philo = philo->num_philo;
	while (1)
	{
		i = 0;
		while (i < n_philo)
		{
			if (monitor_loop(philo, i))
				return ;
			i++;
		}
		usleep(10);
	}
}
