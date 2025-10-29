/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:39:01 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/29 13:00:12 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_current_time(void)
{
	struct		timeval	actual_tv;
	long long	current_time;

	gettimeofday(&actual_tv, NULL);
	current_time = actual_tv.tv_sec * 1000 + actual_tv.tv_usec / 1000;
	return (current_time);
}

int	ft_atoi(char *nptr)
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

int	check_values(int argc, char **argv)
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

void	print_dead(t_philo *philosophers, long long time)
{
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d died\n", time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void    print_start_thinking(t_philo *philosophers, long long time)
{
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is thinking\n", time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void    print_get_fork(t_philo *philosophers, long long time)
{
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d has taken a fork\n", time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void    print_start_eat(t_philo *philosophers, long long time)
{
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is eating\n", time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void	print_start_sleeping(t_philo *philosophers, long long time)
{
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is sleeping\n", time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

long long	check_alive(t_philo *philosophers)
{
	int			time_to_die;
	long long	actual_time_alive;
	long long	time_difference;

	time_to_die = philosophers->data->time_to_die;
	actual_time_alive = get_current_time();
	pthread_mutex_lock(&(philosophers->philo_mutex));
	time_difference = actual_time_alive - philosophers->time_last_eat;
	pthread_mutex_unlock(&(philosophers->philo_mutex));
	if (((long long)time_to_die) < time_difference)
		return (-1);
	else
		return (actual_time_alive);
}

long long	check_sleep_time(t_philo *philosophers, long long time, int sleep)
{
	long long	last_eat;
	int			time_to_die;
	useconds_t	sleep_to_die;

	pthread_mutex_lock(&(philosophers->philo_mutex));
	last_eat = philosophers->time_last_eat;
	pthread_mutex_unlock(&(philosophers->philo_mutex));
	time_to_die = philosophers->data->time_to_die;
	if ((last_eat + (long long) time_to_die) <= (time + (long long) sleep))
	{
		sleep_to_die = (useconds_t) (last_eat + (long long) time_to_die - time);
		usleep(sleep_to_die * 1000);
		return (last_eat + (long long) time_to_die);
	}
	else
		return (0);
}

void	philo_think(t_philo *philosophers)
{
	long long		actual_time_think;

	actual_time_think = check_alive(philosophers);
	if (actual_time_think == -1)
	{
		print_dead(philosophers, actual_time_think);
		pthread_mutex_lock(&(philosophers->philo_mutex));
		philosophers->is_alive = 0;
		pthread_mutex_unlock(&(philosophers->philo_mutex));
		return ;
	}
	print_start_thinking(philosophers, actual_time_think);
	return ;
}

void	philo_get_right_fork(t_philo *philosophers)
{
	long long	actual_time_right_fork;

	actual_time_right_fork = check_alive(philosophers);
   	if (actual_time_right_fork == -1)
	{
		print_dead(philosophers, actual_time_right_fork);
		pthread_mutex_lock(&(philosophers->philo_mutex));
		philosophers->is_alive = 0;
		pthread_mutex_unlock(&(philosophers->philo_mutex));
		return ;
	}
	//printf("Filosofo %d, forbidden %d\n", philosophers->id, philosophers->waiter->id_next_eat - 1);
	pthread_mutex_lock(&(philosophers->data->forks[philosophers->r_fork - 1]));
	print_get_fork(philosophers, actual_time_right_fork);
	return ;
}

void	philo_get_left_fork_and_eat(t_philo *philosopher)
{
	long long	actual_time_left_fork;
	useconds_t	time_to_eat;

	actual_time_left_fork = check_alive(philosopher);
	if (actual_time_left_fork == -1)
	{
		print_dead(philosopher, actual_time_left_fork);
		pthread_mutex_lock(&(philosopher->philo_mutex));
		philosopher->is_alive = 0;
		pthread_mutex_unlock(&(philosopher->philo_mutex));
		return ;
	}
	time_to_eat = (useconds_t) philosopher->data->time_to_eat;
	pthread_mutex_lock(&(philosopher->data->forks[philosopher->l_fork - 1]));
	print_get_fork(philosopher, actual_time_left_fork);
	print_start_eat(philosopher, actual_time_left_fork);
	//printf("El tiempo de comer es: %lld\n", (long long) time_to_eat);
	usleep(time_to_eat * 1000);
	//printf("Termina de comer\n");
	pthread_mutex_unlock(&(philosopher->data->forks[philosopher->l_fork - 1]));
	pthread_mutex_unlock(&(philosopher->data->forks[philosopher->r_fork - 1]));
	return ;
}

void	philo_eat(t_philo *philosopher)
{
	long long	actual_time;
	useconds_t	time_to_eat;

	pthread_mutex_lock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
	actual_time = check_alive(philosopher);
	if (actual_time == -1)
	{
		print_dead(philosopher, actual_time);
		pthread_mutex_lock(&(philosopher->philo_mutex));
		philosopher->is_alive = 0;
		pthread_mutex_unlock(&(philosopher->philo_mutex));
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
		return ;
	}
	print_get_fork(philosopher, actual_time);
	pthread_mutex_lock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
	actual_time = check_alive(philosopher);
	if (actual_time == -1)
	{
		print_dead(philosopher, actual_time);
		pthread_mutex_lock(&(philosopher->philo_mutex));
		philosopher->is_alive = 0;
		pthread_mutex_unlock(&(philosopher->philo_mutex));
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
		return ;
	}
	print_get_fork(philosopher, actual_time);
	time_to_eat = (useconds_t) philosopher->data->time_to_eat;
	print_start_eat(philosopher, actual_time);
	//printf("El tiempo de comer es: %lld\n", (long long) time_to_eat);
	usleep(time_to_eat * 1000);
	//printf("Termina de comer\n");
	pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
	pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
	return ;
}

void	philo_get_sleep(t_philo *philosophers)
{
	long long	actual_time_sleep;
	useconds_t	time_to_sleep;

	actual_time_sleep = check_alive(philosophers);
	time_to_sleep = (useconds_t) philosophers->data->time_to_sleep;
	print_start_sleeping(philosophers, actual_time_sleep);
	usleep(time_to_sleep * 1000);
	return ;
}

int	check_running_simulation(t_philo *philosophers)
{
	int	is_alive;

	pthread_mutex_lock(&(philosophers->philo_mutex));
	is_alive = philosophers->is_alive;
	pthread_mutex_unlock(&(philosophers->philo_mutex));
	return (is_alive);
}

void	*routine(void *arg)
{
	t_philo	*philosophers;

	philosophers = (t_philo *) arg;
	if (philosophers->id % 2 == 0)
        usleep(1000); // Duerme 1ms (o menos) para dar tiempo a los impares
	while (check_running_simulation(philosophers))
	{
		//printf("Entra en la rutina\n");
		philo_think(philosophers);
		//philo_get_right_fork(philosophers);
		//philo_get_left_fork_and_eat(philosophers);
		philo_eat(philosophers);
		philo_get_sleep(philosophers);
		//printf("Hace la rutina\n");
	}
	printf("Sale de la rutina\n");
	pthread_detach(philosophers->thread);
	return (NULL);
}

void	philosophers_start(t_philo_data *philo, long long start_time)
{
	int				i;

	i = 0;
	while (i < philo->num_philo)
	{
		//printf("Se crea el filosofo numero %d\n", i + 1);
		philo->philosophers[i].id = i + 1;
		//printf("el tiempo para empezar a pensar es: %lld\n", first_think);
		philo->philosophers[i].time_last_eat = start_time;
		philo->philosophers[i].is_alive = 1;
		pthread_mutex_init(&(philo->philosophers[i].philo_mutex), NULL);
		pthread_create(&philo->philosophers[i].thread, NULL, routine, &philo->philosophers[i]);
		i++;
	}
}

void	forks_start(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	philosophers(t_philo_data *philo, long long start_time)
{
	int				n;

	n = philo->num_philo;
	forks_start(philo->forks, n);
	philosophers_start(philo, start_time);
}

void	complete_philo_data(int argc, char **argv, t_philo_data **d)
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
	printf("Termina la asignacion de argumentos\n");
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
		i++;
	}
	(*d)->philosophers[0].l_fork = (*d)->num_philo;
	pthread_mutex_init(&((*d)->msg), NULL);
}

int	main(int argc, char **argv)
{
	t_philo_data	*philo;
	long long		start_time;

	//printf("La cantidad de argumentos es: %d\n", argc);
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
	printf("Termina la verificacion de argumentos\n");
	complete_philo_data(argc, argv, &philo);
	printf("Termina de completar el philo_data\n");
	philosophers(philo, start_time);
	return (EXIT_SUCCESS);
}

/*
int	main(void)
{
	pthread_mutex_t	*forks;
	t_philo_data	philo;

	philo.num_philo = 2;
	philo.time_to_die = 1000;
	philo.time_to_eat = 200;
	philo.time_to_sleep = 200;
	philo.number_to_eat = 10;
	forks = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t) * 2);
	forks_start(forks, 2);
	philosophers_start(philo);
	return (1);
}
*/
