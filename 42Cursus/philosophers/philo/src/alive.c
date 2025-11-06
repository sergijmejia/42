/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:22:06 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 16:26:26 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitorize_alive(t_philo *philosopher)
{
	pthread_mutex_lock(&(philosopher->philo_mutex));
	if (philosopher->is_alive == 0)
	{
		pthread_mutex_unlock(&(philosopher->philo_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philosopher->philo_mutex));
	return (0);
}

long long	check_alive(t_philo *philosopher)
{
	int			time_to_die;
	long long	actual_time_alive;
	long long	time_difference;

	if (monitorize_finished(philosopher))
		return (-1);
	if (monitorize_alive(philosopher))
		return (-1);
	time_to_die = philosopher->data->time_to_die;
	actual_time_alive = get_current_time();
	pthread_mutex_lock(&(philosopher->philo_mutex));
	time_difference = actual_time_alive - philosopher->time_last_eat;
	pthread_mutex_unlock(&(philosopher->philo_mutex));
	if (((long long)time_to_die) < time_difference)
	{
		print_dead(philosopher, actual_time_alive);
		pthread_mutex_lock(&(philosopher->data->sim));
		philosopher->data->finished = 1;
		pthread_mutex_unlock(&(philosopher->data->sim));
		pthread_mutex_lock(&(philosopher->philo_mutex));
		philosopher->is_alive = 0;
		pthread_mutex_unlock(&(philosopher->philo_mutex));
		return (-1);
	}
	return (actual_time_alive);
}

int	monitorize_finished(t_philo *philosopher)
{
	int	finished;

	pthread_mutex_lock(&(philosopher->data->sim));
	finished = philosopher->data->finished;
	pthread_mutex_unlock(&(philosopher->data->sim));
	return (finished);
}
