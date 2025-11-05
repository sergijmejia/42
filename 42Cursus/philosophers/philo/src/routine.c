/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:09:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 17:26:43 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Rutina de cada filsofo*/
void	*routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *) arg;
	if (philosopher->id % 2 == 0)
		usleep(philosopher->data->time_to_eat / 2 * 1000);
	while (monitorize_finished(philosopher) != 1)
	{
		if (monitorize_finished(philosopher) != 1)
			philo_think(philosopher);
		if (monitorize_finished(philosopher) != 1)
			philo_eat(philosopher);
		if (monitorize_finished(philosopher) != 1)
			philo_sleep(philosopher);
	}
	return (NULL);
}

/*Rutina para un unico filosofo*/
void	*routine_single(void *arg)
{
	t_philo		*philosopher;
	long long	actual_time;

	philosopher = (t_philo *) arg;
	actual_time = check_alive(philosopher);
	print_get_fork(philosopher, actual_time);
	usleep(philosopher->data->time_to_die * 1000 + 1000);
	actual_time = check_alive(philosopher);
	if (actual_time != -1)
	{
		print_dead(philosopher, actual_time);
		pthread_mutex_lock(&(philosopher->data->sim));
		philosopher->data->finished = 1;
		pthread_mutex_unlock(&(philosopher->data->sim));
		pthread_mutex_lock(&(philosopher->philo_mutex));
		philosopher->is_alive = 0;
		pthread_mutex_unlock(&(philosopher->philo_mutex));
	}
	return (NULL);
}
