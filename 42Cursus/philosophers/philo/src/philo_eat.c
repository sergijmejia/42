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

static int	philo_dead_eat(t_philo *philosopher, int r_l)
{
	if (r_l == 1)
		pthread_mutex_unlock(&(philosopher->data->forks
			[(philosopher->r_fork) - 1]));
	else
	{
		pthread_mutex_unlock(&(philosopher->data->forks
			[(philosopher->r_fork) - 1]));
		pthread_mutex_unlock(&(philosopher->data->forks
			[(philosopher->l_fork) - 1]));
	}
	return (0);
}

static int	first_fork(t_philo *philosopher)
{
	int			r_fork;

	r_fork = philosopher->r_fork - 1;
	while (1)
	{
		if (monitorize_finished(philosopher))
			return (1);
		pthread_mutex_lock(&(philosopher->data->read_forks));
		if (philosopher->data->available_forks[r_fork])
		{
			philosopher->data->available_forks[r_fork] = 0;
			pthread_mutex_lock(&(philosopher->data->forks
				[(philosopher->r_fork) - 1]));
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			usleep(10);
		}
	}
	return (0);
}

static int	second_fork(t_philo *philosopher)
{
	int			l_fork;

	l_fork = philosopher->l_fork - 1;
	while (1)
	{
		if (monitorize_finished(philosopher))
			return (1);
		pthread_mutex_lock(&(philosopher->data->read_forks));
		if (philosopher->data->available_forks[l_fork])
		{
			philosopher->data->available_forks[l_fork] = 0;
			pthread_mutex_lock(&(philosopher->data->forks
				[(philosopher->l_fork) - 1]));
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			usleep(10);
		}
	}
	return (0);
}

static long long	get_forks(t_philo *philosopher)
{
	long long	actual_time;
	int			r_fork;
	int			l_fork;

	r_fork = philosopher->r_fork - 1;
	l_fork = philosopher->l_fork - 1;
	if (first_fork(philosopher))
		return (0);
	actual_time = check_alive(philosopher);
	if (actual_time == -1)
		return (philo_dead_eat(philosopher, 1));
	print_get_fork(philosopher, actual_time);
	if (second_fork(philosopher))
		return (philo_dead_eat(philosopher, 1));
	actual_time = check_alive(philosopher);
	if (actual_time == -1)
		return (philo_dead_eat(philosopher, 2));
	print_get_fork(philosopher, actual_time);
	return (actual_time);
}

void	philo_eat(t_philo *philosopher)
{
	long long	actual_time;
	useconds_t	time_to_eat;

	actual_time = get_forks(philosopher);
	if (actual_time == 0)
		return ;
	time_to_eat = (useconds_t) philosopher->data->time_to_eat;
	pthread_mutex_lock(&(philosopher->philo_mutex));
	philosopher->time_last_eat = actual_time;
	philosopher->num_eat = philosopher->num_eat + 1;
	pthread_mutex_unlock(&(philosopher->philo_mutex));
	print_start_eat(philosopher, actual_time);
	usleep(time_to_eat * 1000);
	pthread_mutex_lock(&(philosopher->data->read_forks));
	philosopher->data->available_forks[philosopher->r_fork - 1] = 1;
	philosopher->data->available_forks[philosopher->l_fork - 1] = 1;
	pthread_mutex_unlock(&(philosopher->data->forks
		[(philosopher->l_fork) - 1]));
	pthread_mutex_unlock(&(philosopher->data->forks
		[(philosopher->r_fork) - 1]));
	pthread_mutex_unlock(&(philosopher->data->read_forks));
	return ;
}
