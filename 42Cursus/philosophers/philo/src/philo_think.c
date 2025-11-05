/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:38:51 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 16:39:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Funcion que gestiona la fase think de los filosofos*/
void	philo_think(t_philo *philosophers)
{
	long long		actual_time_think;

	actual_time_think = check_alive(philosophers);
	if (actual_time_think == -1)
		return ;
	print_start_thinking(philosophers, actual_time_think);
	return ;
}
