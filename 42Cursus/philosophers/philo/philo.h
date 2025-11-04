/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:33:36 by smejia-a          #+#    #+#             */
/*   Updated: 2025/05/09 20:51:26 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philo_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_to_eat;
	long long		time_start;
	int				finished;
	int				*available_forks;
	pthread_mutex_t	*forks;
	pthread_mutex_t	read_forks;
	pthread_mutex_t	msg;
	pthread_mutex_t	sim;
	struct s_philo	*philosophers;
} t_philo_data;

typedef struct	s_philo
{
	pthread_t		thread;
	long long		time_last_eat; //<---requiere mutex
	int				id;
	int				l_fork; 
	int				r_fork;
	int				is_alive; //<---requiere mutex
	int				num_eat; //<---requiere mutex
	pthread_mutex_t	philo_mutex;
	t_philo_data	*data;
} t_philo;

#endif
