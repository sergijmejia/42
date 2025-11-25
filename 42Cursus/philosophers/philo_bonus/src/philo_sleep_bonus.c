/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:36:06 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/18 14:05:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep(t_philosopher *philosopher)
{
	long long	actual_time_sleep;

	actual_time_sleep = get_current_time();
	print_start_sleep(philosopher->philo, actual_time_sleep, philosopher->id);
	usleep(philosopher->philo->time_to_sleep * 1000);
	return ;
}
