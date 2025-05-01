/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:39:01 by smejia-a          #+#    #+#             */
/*   Updated: 2025/05/01 19:24:56 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	print_dead(int id, long long time)
{
	printf("%lld %d died\n", time, id);
}

void    print_start_thinking(int id, long long time)
{
	printf("%lld %d is thinking\n", time, id);
}

void    print_get_fork(int id, long long time)
{
	printf("%lld %d has taken a fork\n", time, id);
}

void    print_start_eat(int id, long long time)
{
	printf("%lld %d is eating\n", time, id);
}

void	print_start_sleeping(int id, long long time)
{
	printf("%lld %d is sleeping\n", time, id);
}

long long	check_alive(t_philo *philosophers)
{
	int				time_to_die;
	struct timeval	actual_tv;
	long long		actual_time;

	time_to_die = philosophers->data.time_to_die;
	gettimeofday(&actual_tv, NULL);
	actual_time = actual_tv.tv_sec * 1000 + actual_tv.tv_usec / 1000;
	if (((long long)time_to_die) < (actual_time - philosophers->time_last_eat))
		return (-1);
	else
		return (actual_time);
}

long long	check_sleep_time(t_philo *philosophers, long long time, int sleep)
{
	long long	last_eat;
	int			time_to_die;
	useconds_t	sleep_to_die;

	last_eat = philosophers->time_last_eat;
	time_to_die = philosophers->data.time_to_die;
	if ((last_eat + (long long) time_to_die) <= (time + (long long) sleep))
	{
		sleep_to_die = (useconds_t) (last_eat + (long long) time_to_die - time);
		usleep(sleep_to_die);
		return (last_eat + (long long) time_to_die);
	}
	else
		return (0);
}

void	next_allowed_philosopher(t_philo *philosophers)
{
	philosophers->waiter->id_next_eat++;
	if (philosophers->waiter->id_next_eat > philosophers->data.number_of_philo)
		philosophers->waiter->id_next_eat = 1;
	printf("El siguiente que puede comer es: %d\n", philosophers->waiter->id_next_eat);
	return ;
}

void	philo_think(t_philo *philosophers)
{
	long long		actual_time;

	actual_time = check_alive(philosophers);
	if (actual_time == -1)
	{
		print_dead(philosophers->id, actual_time);
		philosophers->is_alive = 0;
		return ;
	}
	else
	{
		print_start_thinking(philosophers->id, actual_time);
		philosophers->state = 1;
		return ;
	}
}

void	philo_get_right_fork(t_philo *philosophers)
{
	int			id_forbidden;
	long long	actual_time;

	actual_time = check_alive(philosophers);
    if (actual_time == -1)
	{
		print_dead(philosophers->id, actual_time);
		philosophers->is_alive = 0;
		return ;
	}
	id_forbidden = philosophers->waiter->id_next_eat - 1;
	if (id_forbidden == 0)
		id_forbidden = philosophers->data.number_of_philo;
	if (philosophers->id == id_forbidden)
		return ;
	else
	{
		print_get_fork(philosophers->id, actual_time);
		pthread_mutex_lock(philosophers->right_fork);
		philosophers->state = 2;
		return ;
	}
}

void	philo_get_left_fork_and_eat(t_philo *philosophers)
{
	int			id_allowed;
	long long	actual_time;
	useconds_t	time_to_eat;

	actual_time = check_alive(philosophers);
	if (actual_time == -1)
	{
		print_dead(philosophers->id, actual_time);
		philosophers->is_alive = 0;
		return ;
	}
	time_to_eat = (useconds_t) philosophers->data.time_to_eat;
	id_allowed = philosophers->waiter->id_next_eat;
	if (philosophers->id == id_allowed)
	{
		print_get_fork(philosophers->id, actual_time);
		print_start_eat(philosophers->id, actual_time);
		pthread_mutex_lock(philosophers->left_fork);
		//printf("El tiempo de comer es: %lld\n", (long long) time_to_eat);
		usleep(time_to_eat);
		//printf("Termina de comer\n");
		pthread_mutex_unlock(philosophers->left_fork);
		pthread_mutex_unlock(philosophers->right_fork);
		next_allowed_philosopher(philosophers);
		philosophers->state = 3;
		return ;
	}
	else
		return ;
}

void	philo_get_sleep(t_philo *philosophers)
{
	long long	actual_time;
	useconds_t	time_to_sleep;
	long long	dead_time;

	actual_time = check_alive(philosophers);
	if (actual_time == -1)
	{
		print_dead(philosophers->id, actual_time);
		philosophers->is_alive = 0;
		return ;
	}
	time_to_sleep = (useconds_t) philosophers->data.time_to_sleep;
	print_start_sleeping(philosophers->id, actual_time);
	dead_time = check_sleep_time(philosophers, actual_time, time_to_sleep);
	if (dead_time > 0)
	{
		print_dead(philosophers->id, dead_time);
		philosophers->is_alive = 0;
		return ;
	}
	usleep(time_to_sleep);
	philosophers->state = 0;
	return ;
}

void	*routine(void *arg)
{
	t_philo		*philosophers;
	useconds_t	time_to_sleep;
	useconds_t	time_to_eat;

	philosophers = (t_philo *) arg;
	time_to_sleep = (useconds_t) philosophers->data.time_to_sleep;
	time_to_eat = (useconds_t) philosophers->data.time_to_eat;
	while (philosophers->is_alive)
	{
		if (philosophers->state == 0)
			philo_think(philosophers);
		else if (philosophers->state == 1)
			philo_get_right_fork(philosophers);
		else if (philosophers->state == 2)
			philo_get_left_fork_and_eat(philosophers);
		else if (philosophers->state == 3)
			philo_get_sleep(philosophers);
	}
	printf("Sale de la rutina\n");
	pthread_detach(philosophers->thread);
	return (NULL);
}

void	philosophers_start(t_philo *philosophers, t_philo_data philo, pthread_mutex_t *forks, t_waiter *waiter)
{
	int				i;
	long long		first_think;
	struct timeval	actual_tv;

	i = 0;
	while (i < philo.number_of_philo)
	{
		printf("Se crea el filosofo numero %d\n", i + 1);
		philosophers[i].id = i + 1;
		gettimeofday(&actual_tv, NULL);
		first_think = actual_tv.tv_sec * 1000 + actual_tv.tv_usec / 1000;
		//printf("el tiempo para empezar a pensar es: %lld\n", first_think);
		philosophers[i].data = philo;
		philosophers[i].time_last_eat = first_think;
		philosophers[i].left_fork = &forks[i];
		if (i == (philo.number_of_philo - 1))
			philosophers[i].right_fork = &forks[0];
		else
			philosophers[i].right_fork = &forks[i + 1];
		philosophers[i].state = 0;
		philosophers[i].is_alive = 1;
		philosophers[i].waiter = waiter;
		pthread_create(&philosophers[i].thread, NULL, routine, &philosophers[i]);
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

void	philosophers(t_philo_data philo)
{
	t_philo	*philosophers;
	pthread_mutex_t *forks;
	t_waiter	waiter;
	int	n;

	n = philo.number_of_philo;
	philosophers = (t_philo *) malloc (sizeof (t_philo) * n);
	forks = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t) * n);
	forks_start(forks, n);
	waiter.id_next_eat = 1;
	philosophers_start(philosophers, philo, forks, &waiter);
}

void	complete_philo_data(int argc, char **argv, t_philo_data *philo)
{
	philo->number_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->number_to_eat = ft_atoi(argv[5]);
	else
		philo->number_to_eat = -1;
}

int	main(int argc, char **argv)
{
	t_philo_data philo;

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
	complete_philo_data(argc, argv, &philo);
	philosophers(philo);
	return (EXIT_SUCCESS);
}
