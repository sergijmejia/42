/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:05:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/18 14:05:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_dead(t_philo_data *philo, long long time, int id)
{
	long long	print_time;

	print_time = time - philo->time_start;
	sem_wait(philo->print);
	printf("%lld %d died\n", print_time, id);
	sem_post(philo->print);
}

void	print_start_think(t_philo_data *philo, long long time, int id)
{
	long long	print_time;

	print_time = time - philo->time_start;
	sem_wait(philo->print);
	printf("%lld %d is thinking\n", print_time, id);
	sem_post(philo->print);
}

void	print_get_fork(t_philo_data *philo, long long time, int id)
{
	long long	print_time;

	print_time = time - philo->time_start;
	sem_wait(philo->print);
	printf("%lld %d has taken a fork\n", print_time, id);
	sem_post(philo->print);
}

void	print_start_eat(t_philo_data *philo, long long time, int id)
{
	long long	print_time;

	print_time = time - philo->time_start;
	sem_wait(philo->print);
	printf("%lld %d is eating\n", print_time, id);
	sem_post(philo->print);
}

void	print_start_sleep(t_philo_data *philo, long long time, int id)
{
	long long	print_time;

	print_time = time - philo->time_start;
	sem_wait(philo->print);
	printf("%lld %d is sleeping\n", print_time, id);
	sem_post(philo->print);
}
