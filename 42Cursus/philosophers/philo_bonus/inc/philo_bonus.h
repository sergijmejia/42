/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:33:36 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/24 12:06:13 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_philo_data
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_to_eat;
	long long	time_start;
	int			available_forks;
	int			philosophers_room;
	int			num_print;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*room;
}	t_philo_data;

typedef struct s_philosopher
{
	t_philo_data	*philo;
	sem_t			*check_philo;
	int				id;
	int				num_eat;
	long long		time_last_eat;
}	t_philosopher;

/*Print*/
void			print_dead(t_philo_data *philo, long long time, int id);
void			print_start_think(t_philo_data *philo, long long time, int id);
void			print_get_fork(t_philo_data *philo, long long time, int id);
void			print_start_eat(t_philo_data *philo, long long time, int id);
void			print_start_sleep(t_philo_data *philo, long long time, int id);

/*Complete_data*/
t_philo_data	**complete_philo_data(int argc, char **argv,
					t_philo_data **d, long long start_time);

/*Routine*/
int				start_routine(t_philo_data *philo, int id);

/*Eat*/
void			philo_eat(t_philosopher *philosopher);

/*Sleep*/
void			philo_sleep(t_philosopher *philosopher);

/*Think*/
void			philo_think(t_philosopher *philosopher);

/*Monitor*/
int				monitor(t_philo_data *philo, pid_t *pids);

/*Utils*/
int				str_is_num(char *str);
long long		get_current_time(void);
long long		ft_atoll(char *nptr);
int				ft_atoi(char *nptr);

/*Input values*/
int				check_values(int argc, char **argv);

#endif
