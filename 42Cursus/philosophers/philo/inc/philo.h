/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:33:36 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 17:24:09 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo_data
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
}	t_philo_data;

typedef struct s_philo
{
	pthread_t		thread;
	long long		time_last_eat;
	int				id;
	int				l_fork;
	int				r_fork;
	int				is_alive;
	int				num_eat;
	pthread_mutex_t	philo_mutex;
	t_philo_data	*data;
}	t_philo;

/*Print*/
void			print_dead(t_philo *philosophers, long long time);
void			print_start_thinking(t_philo *philosophers, long long time);
void			print_get_fork(t_philo *philosophers, long long time);
void			print_start_eat(t_philo *philosophers, long long time);
void			print_start_sleeping(t_philo *philosophers, long long time);

/*Complete_data*/
t_philo_data	**complete_philo_data(int argc, char **argv,
					t_philo_data **d, long long start_time);

/*Routine*/
void			*routine(void *arg);
void			*routine_single(void *arg);

/*Eat*/
void			philo_eat(t_philo *philosopher);

/*Sleep*/
void			philo_sleep(t_philo *philosophers);

/*Think*/
void			philo_think(t_philo *philosophers);

/*Monitor*/
void			monitor(t_philo_data *philo);

/*Alive*/
int				monitorize_finished(t_philo *philosopher);
long long		check_alive(t_philo *philosopher);

/*Utils*/
int				str_is_num(char *str);
long long		get_current_time(void);
long long		ft_atoll(char *nptr);
int				ft_atoi(char *nptr);

/*Input values*/
int				check_values(int argc, char **argv);

#endif
