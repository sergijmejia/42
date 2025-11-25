/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:30:46 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/18 16:25:35 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philosopher *philosopher)
{
	long long	actual_time_eat;

	sem_wait(philosopher->philo->room);
	sem_wait(philosopher->philo->forks);
	actual_time_eat = get_current_time();
	print_get_fork(philosopher->philo, actual_time_eat, philosopher->id);
	sem_wait(philosopher->philo->forks);
	actual_time_eat = get_current_time();
	print_get_fork(philosopher->philo, actual_time_eat, philosopher->id);
	print_start_eat(philosopher->philo, actual_time_eat, philosopher->id);
	sem_wait(philosopher->check_philo);
	philosopher->time_last_eat = actual_time_eat;
	if (philosopher->philo->number_to_eat != -1)
		philosopher->num_eat++;
	sem_post(philosopher->check_philo);
	usleep(philosopher->philo->time_to_eat * 1000);
	sem_post(philosopher->philo->forks);
	sem_post(philosopher->philo->forks);
	sem_post(philosopher->philo->room);
	return ;
}
