/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:30:46 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 16:32:33 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Funcion que gestiona el dead durante la fase eat.
Los mutex de los forks activos: 1 solo right, 2 solo left, 3 ambos*/
static void	philo_dead_eat(t_philo *philosopher, int r_l)
{
	if (r_l == 1)
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
	else if (r_l == 2)
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
	else
	{
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
	}
	return ;
}

/*Funcion que gestiona la fase eat de los filosofos*/
void	philo_eat(t_philo *philosopher)
{
	long long	actual_time;
	useconds_t	time_to_eat;
	int			r_fork;
	int			l_fork;

	r_fork = philosopher->r_fork - 1;
	l_fork = philosopher->l_fork - 1;
	while (1)
	{
		if (monitorize_finished(philosopher))
			return ;
		pthread_mutex_lock(&(philosopher->data->read_forks));
		if (philosopher->data->available_forks[r_fork])
		{
			philosopher->data->available_forks[r_fork] = 0;
			pthread_mutex_lock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			usleep(100);
		}
	}
	actual_time = check_alive(philosopher);
	if (actual_time == -1)
			return (philo_dead_eat(philosopher, 3));

	print_get_fork(philosopher, actual_time);
	while (1)
	{
		if (monitorize_finished(philosopher))
			return (philo_dead_eat(philosopher, 1));
		pthread_mutex_lock(&(philosopher->data->read_forks));
		if (philosopher->data->available_forks[l_fork])
		{
			philosopher->data->available_forks[l_fork] = 0;
			pthread_mutex_lock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			usleep(100);
		}
	}
	actual_time = check_alive(philosopher);
	if (actual_time == -1)
			return (philo_dead_eat(philosopher, 3));

	print_get_fork(philosopher, actual_time);
	time_to_eat = (useconds_t) philosopher->data->time_to_eat;
	pthread_mutex_lock(&(philosopher->philo_mutex));
	philosopher->time_last_eat = actual_time;
	philosopher->num_eat = philosopher->num_eat + 1;
	pthread_mutex_unlock(&(philosopher->philo_mutex));
	print_start_eat(philosopher, actual_time);
	usleep(time_to_eat * 1000);
	pthread_mutex_lock(&(philosopher->data->read_forks));
	philosopher->data->available_forks[r_fork] = 1;
	philosopher->data->available_forks[l_fork] = 1;
	pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
	pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
	pthread_mutex_unlock(&(philosopher->data->read_forks));
	return ;
}
