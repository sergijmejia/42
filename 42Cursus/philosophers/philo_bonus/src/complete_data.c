/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:06:26 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/14 13:40:40 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_data	**complete_philo_data(int argc, char **argv,
					t_philo_data **d, long long start_time)
{
	(*d)->num_philo = ft_atoi(argv[1]);
	(*d)->time_to_die = ft_atoi(argv[2]);
	(*d)->time_to_eat = ft_atoi(argv[3]);
	(*d)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*d)->number_to_eat = ft_atoi(argv[5]);
	else
		(*d)->number_to_eat = -1;
	(*d)->time_start = start_time;
	(*d)->available_forks = ft_atoi(argv[1]);
	(*d)->philosophers_room = ft_atoi(argv[1]) - 1;
	(*d)->print = 1;
	return (d);
}
