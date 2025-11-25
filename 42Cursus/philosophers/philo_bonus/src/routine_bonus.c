/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:09:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/24 12:57:16 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*fix_name(int num_len)
{
	char	*name;

	name = (char *) malloc ((8 + num_len) * sizeof(char));
	if (name == NULL)
		return (NULL);
	name[0] = '/';
	name[1] = 'c';
	name[2] = 'h';
	name[3] = 'e';
	name[4] = 'c';
	name[5] = 'k';
	name[6] = '_';
	name[7 + num_len] = '\0';
	return (name);
}

static char	*create_name(int counter)
{
	char	*name;
	int		num_len;
	int		aux;

	aux = counter;
	num_len = 0;
	while (aux > 0)
	{
		aux = aux / 10;
		num_len++;
	}
	name = fix_name(num_len);
	if (name == NULL)
		return (NULL);
	while (counter > 0)
	{
		name[6 + num_len] = counter % 10 + '0';
		counter = counter / 10;
		num_len--;
	}
	return (name);
}

static void	*routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) arg;
	while (1)
	{
		philo_think(philosopher);
		philo_eat(philosopher);
		sem_wait(philosopher->check_philo);
		if (philosopher->philo->number_to_eat > 0 && (
				philosopher->num_eat >= philosopher->philo->number_to_eat))
		{
			sem_post(philosopher->check_philo);
			exit(EXIT_SUCCESS);
		}
		sem_post(philosopher->check_philo);
		philo_sleep(philosopher);
	}
	return (NULL);
}

static t_philosopher	*philosopher_data(t_philosopher *philosopher,
							t_philo_data *philo)
{
	char	*name;

	philosopher->philo = philo;
	philosopher->num_eat = 0;
	philosopher->time_last_eat = philo->time_start;
	name = create_name(philosopher->id);
	if (name == NULL)
	{
		write(2, "Memory error\n", 13);
		return (NULL);
	}
	philosopher->check_philo = sem_open(name, O_CREAT, 0644, 1);
	sem_unlink(name);
	free(name);
	return (philosopher);
}

int	start_routine(t_philo_data *philo, int id)
{
	pthread_t		thread;
	long long		actual_time;
	t_philosopher	philosopher;

	philosopher.id = id;
	if (philosopher_data(&philosopher, philo) == NULL)
		return (1);
	pthread_create(&thread, NULL, routine, &philosopher);
	pthread_detach(thread);
	while (1)
	{
		actual_time = get_current_time();
		sem_wait(philosopher.check_philo);
		if ((actual_time - philosopher.time_last_eat) > philo->time_to_die)
		{
			print_dead(philo, actual_time, id);
			sem_post(philosopher.check_philo);
			return (1);
		}
		sem_post(philosopher.check_philo);
		usleep(10);
	}
}
