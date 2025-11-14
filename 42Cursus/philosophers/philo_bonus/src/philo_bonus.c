/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:10:58 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/06 10:19:05 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosophers_start(t_philo_data *philo, long long start_time)
{
	pid_t	aux;
	pid_t	*pid;
	int		i;
	long long	time_last_eat;		

	i = 0;
	pid = (pid_t *) malloc ((philo->num_philo) * sizeof(pid_t));
	if (pid == NULL)
		return ;
	while (i < philo->num_philo)
	{
		aux = fork();
		if (aux == -1)
		{
		
		}
		if (aux == 0)
		{
			//hijo
			routine(philo, start_time);
			break ; //->para que al morir el hijo salga del bucle
		}
		else
		{
			//padre
			pid[i] = aux;
			i++; //->para crear el siguiente hijo
		}
	}
	waitpid()
	return ;
}

static void	philosophers_end(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		pthread_join(philo->philosophers[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		pthread_mutex_destroy(&philo->philosophers[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->read_forks);
	pthread_mutex_destroy(&philo->msg);
	pthread_mutex_destroy(&philo->sim);
	free(philo->forks);
	free(philo->philosophers);
	free(philo);
	return ;
}

int	main(int argc, char **argv)
{
	t_philo_data	*philo;
	long long		start_time;

	if (check_values(argc, argv))
		return (EXIT_FAILURE);
	philo = (t_philo_data *) malloc (sizeof(t_philo_data));
	if (!philo)
		return (EXIT_FAILURE);
	start_time = get_current_time();
	if (!(complete_philo_data(argc, argv, &philo, start_time)))
	{
		free(philo);
		return (EXIT_FAILURE);
	}
	philosophers_start(philo, start_time);
	waitpid
	philosophers_end(philo);
	return (EXIT_SUCCESS);
}
