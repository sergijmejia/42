/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:55:44 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 17:25:29 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Funcion que te devuelve el tiempo actual en milisegundos*/
long long	get_current_time(void)
{
	struct timeval	actual_tv;
	long long		current_time;

	gettimeofday(&actual_tv, NULL);
	current_time = actual_tv.tv_sec * 1000 + actual_tv.tv_usec / 1000;
	return (current_time);
}
