/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:36:06 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 16:37:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philosophers)
{
	long long	actual_time_sleep;
	useconds_t	time_to_sleep;

	actual_time_sleep = check_alive(philosophers);
	if (actual_time_sleep == -1)
		return ;
	time_to_sleep = (useconds_t) philosophers->data->time_to_sleep;
	print_start_sleeping(philosophers, actual_time_sleep);
	usleep(time_to_sleep * 1000);
	return ;
}
