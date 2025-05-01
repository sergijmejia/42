/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:33:36 by smejia-a          #+#    #+#             */
/*   Updated: 2025/05/01 18:12:56 by smejia-a         ###   ########.fr       */
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
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_to_eat;
} t_philo_data;

typedef struct	s_waiter
{
	int				id_next_eat;
} t_waiter;

typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	long long		time_last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				state;
	int				is_alive;
	t_waiter		*waiter;
	t_philo_data	data;
} t_philo;

#endif
