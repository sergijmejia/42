/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:10:58 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/05 16:14:28 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Funcion que transforma un char en int*/
static int	ft_atoi(char *nptr)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	if (!nptr)
		return (0);
	while (*nptr && ((*nptr >= '\t' && *nptr <= '\r') || (*nptr == ' ')))
		nptr++;
	if (*nptr == '-')
		negative = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	return (res * negative);
}

/*Funcion que verifica que los valores ingresados son validos para el proyecto*/
static int	check_values(int argc, char **argv)
{
	int	arg1;
	int	arg2;
	int	arg3;
	int arg4;
	int	arg5;

	arg1 = ft_atoi(argv[1]);
	arg2 = ft_atoi(argv[2]);
	arg3 = ft_atoi(argv[3]);
	arg4 = ft_atoi(argv[4]);
	if (arg1 <= 0 || arg2 <= 0 || arg3 <= 0 || arg4 <= 0)
		return (1);
	if (argc == 6)
	{
		arg5 = ft_atoi(argv[5]);
		if (arg5 <= 0)
			return (1);
	}
	return (0);
}

/*Funcion que complementa la estructura tipo s_philo_data*/
static void	complete_philo_data(int argc, char **argv, t_philo_data **d)
{
	int	i;

	(*d)->num_philo = ft_atoi(argv[1]);
	(*d)->time_to_die = ft_atoi(argv[2]);
	(*d)->time_to_eat = ft_atoi(argv[3]);
	(*d)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*d)->number_to_eat = ft_atoi(argv[5]);
	else
		(*d)->number_to_eat = -1;
	(*d)->time_start = get_current_time();
	(*d)->finished = 0;
	(*d)->available_forks = (int *) malloc (sizeof(int)*((*d)->num_philo));
	(*d)->forks = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t)*((*d)->num_philo));
	(*d)->philosophers = (t_philo *) malloc (sizeof(t_philo)*((*d)->num_philo));
	i = 0;
	while (i < (*d)->num_philo)
	{
		pthread_mutex_init(&((*d)->forks[i]), NULL);
		(*d)->philosophers[i].r_fork = i + 1;
		(*d)->philosophers[i].l_fork = i;
		(*d)->philosophers[i].id = i + 1;
		(*d)->philosophers[i].data = (*d);
		(*d)->available_forks[i] = 1;
		i++;
	}
	(*d)->philosophers[0].l_fork = (*d)->num_philo;
	pthread_mutex_init(&((*d)->read_forks), NULL);
	pthread_mutex_init(&((*d)->msg), NULL);
	pthread_mutex_init(&((*d)->sim), NULL);
}

/*Funcion que inicializa los filosofos*/
void	philosophers_start(t_philo_data *philo, long long start_time)
{
	int				i;

	i = 0;
	if (philo->num_philo == 1)
	{
		philo->philosophers[0].id = 1;
		philo->philosophers[0].time_last_eat = start_time;
		philo->philosophers[0].is_alive = 1;
		philo->philosophers[0].num_eat = 0;
		pthread_mutex_init(&(philo->philosophers[0].philo_mutex), NULL);
		pthread_create(&philo->philosophers[0].thread, NULL, routine_single, &philo->philosophers[0]);
		return ;
	}
	i = 0;
	while (i < philo->num_philo)
	{
		philo->philosophers[i].id = i + 1;
		philo->philosophers[i].time_last_eat = start_time;
		philo->philosophers[i].is_alive = 1;
		philo->philosophers[i].num_eat = 0;
		pthread_mutex_init(&(philo->philosophers[i].philo_mutex), NULL);
		pthread_create(&philo->philosophers[i].thread, NULL, routine, &philo->philosophers[i]);
		pthread_detach(philo->philosophers[i].thread);
		i++;
	}
	return ;
}

/*Funcion que inicia el proceo*/
static void	philosophers(t_philo_data *philo, long long start_time)
{
	int				n;

	n = philo->num_philo;
	philosophers_start(philo, start_time);
}

/*PHILOSOPHERS*/
int	main(int argc, char **argv)
{
	t_philo_data	*philo;
	long long		start_time;
	int				i;

	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments.\n", 27);
		exit(EXIT_FAILURE);
	}
	if (check_values(argc, argv))
	{
		write(2, "Negative or nul arguments.\n", 27);
		exit(EXIT_FAILURE);
	}
	philo = (t_philo_data *) malloc (sizeof(t_philo_data));
	if (!philo)
		return (EXIT_FAILURE);
	start_time = get_current_time();
	complete_philo_data(argc, argv, &philo);
	philosophers(philo, start_time);
	monitor(philo);
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
	return (EXIT_SUCCESS);
}
