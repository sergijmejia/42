/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:38:51 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/18 16:26:20 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_think(t_philosopher *philosopher)
{
	long long		actual_time_think;

	actual_time_think = get_current_time();
	print_start_think(philosopher->philo, actual_time_think, philosopher->id);
	return ;
}
