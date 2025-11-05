/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:05:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 17:27:25 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d died\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void	print_start_thinking(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is thinking\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void	print_get_fork(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d has taken a fork\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void	print_start_eat(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is eating\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void	print_start_sleeping(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is sleeping\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}
