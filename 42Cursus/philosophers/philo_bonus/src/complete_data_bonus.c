/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_data_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:06:26 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/24 12:02:11 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo_data	**complete_philo_data(int argc, char **argv,
					t_philo_data **d, long long start_time)
{
	int	i;

	i = 0;
	sem_unlink("/p_forks");
	sem_unlink("/p_print");
	sem_unlink("/p_room");
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
	(*d)->num_print = 1;
	(*d)->forks = sem_open("/p_forks", O_CREAT, 0644, (*d)->available_forks);
	(*d)->print = sem_open("/p_print", O_CREAT, 0644, (*d)->num_print);
	(*d)->room = sem_open("/p_room", O_CREAT, 0644, (*d)->philosophers_room);
	return (d);
}
