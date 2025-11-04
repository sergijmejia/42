/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:39:01 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/31 14:54:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d died\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void    print_start_thinking(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is thinking\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void    print_get_fork(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d has taken a fork\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void    print_start_eat(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is eating\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

void	print_start_sleeping(t_philo *philosophers, long long time)
{
	long long	print_time;

	print_time = time - philosophers->data->time_start;
	pthread_mutex_lock(&(philosophers->data->msg));
	printf("%lld %d is sleeping\n", print_time, philosophers->id);
	pthread_mutex_unlock(&(philosophers->data->msg));
}

int	monitorize_finished(t_philo *philosopher)
{
	int	finished;

	pthread_mutex_lock(&(philosopher->data->sim));
	finished = philosopher->data->finished;
	pthread_mutex_unlock(&(philosopher->data->sim));
	return (finished);
}

long long	check_alive(t_philo *philosopher)
{
	int			time_to_die;
	long long	actual_time_alive;
	long long	time_difference;

	if (monitorize_finished(philosopher))
		return (-1);
	pthread_mutex_lock(&(philosopher->philo_mutex));
	if (philosopher->is_alive == 0)
		return (-1);
	pthread_mutex_unlock(&(philosopher->philo_mutex));
	time_to_die = philosopher->data->time_to_die;
	actual_time_alive = get_current_time();
	pthread_mutex_lock(&(philosopher->philo_mutex));
	time_difference = actual_time_alive - philosopher->time_last_eat;
	pthread_mutex_unlock(&(philosopher->philo_mutex));
	if (((long long)time_to_die) < time_difference)
	{
		print_dead(philosopher, actual_time_alive);
		pthread_mutex_lock(&(philosopher->data->sim));
		philosopher->data->finished = 1;
		pthread_mutex_unlock(&(philosopher->data->sim));
		pthread_mutex_lock(&(philosopher->philo_mutex));
		philosopher->is_alive = 0;
		pthread_mutex_unlock(&(philosopher->philo_mutex));
		return (-1);
	}
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
		return ;
	print_start_thinking(philosophers, actual_time_think);
	return ;
}

/*Funcion que gestiona el dead durante la fase eat.
Los mutex de los forks activos: 1 solo right, 2 solo left, 3 ambos*/
void	philo_dead_eat(t_philo *philosopher, int r_l)
{
	if (r_l == 1)
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
	else if (r_l == 2)
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
	else
	{
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
		pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
	}
	return ;
}

void	philo_eat(t_philo *philosopher)
{
	long long	actual_time;
	useconds_t	time_to_eat;
	//int			r_l;
	int			r_fork;
	int			l_fork;
	/*if (philosopher->id % 2 == 0)
	{*/
	//philo = philosopher->id;

	r_fork = philosopher->r_fork - 1;
	l_fork = philosopher->l_fork - 1;
	while (1)
	{
		if (monitorize_finished(philosopher))
			return ;
		pthread_mutex_lock(&(philosopher->data->read_forks));
		if (philosopher->data->available_forks[r_fork])
		{
			philosopher->data->available_forks[r_fork] = 0;
			pthread_mutex_lock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			usleep(100);
		}
	}
	actual_time = check_alive(philosopher);
	if (actual_time == -1)
			return (philo_dead_eat(philosopher, 3));

	print_get_fork(philosopher, actual_time);
	while (1)
	{
		if (monitorize_finished(philosopher))
			return (philo_dead_eat(philosopher, 1));
		pthread_mutex_lock(&(philosopher->data->read_forks));
		if (philosopher->data->available_forks[l_fork])
		{
			philosopher->data->available_forks[l_fork] = 0;
			pthread_mutex_lock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philosopher->data->read_forks));
			usleep(100);
		}
	}
	actual_time = check_alive(philosopher);
	if (actual_time == -1)
			return (philo_dead_eat(philosopher, 3));

	//print_get_fork(philosopher, actual_time);
	print_get_fork(philosopher, actual_time);
	time_to_eat = (useconds_t) philosopher->data->time_to_eat;
	pthread_mutex_lock(&(philosopher->philo_mutex));
	philosopher->time_last_eat = actual_time;
	philosopher->num_eat = philosopher->num_eat + 1;
	pthread_mutex_unlock(&(philosopher->philo_mutex));
	print_start_eat(philosopher, actual_time);
	usleep(time_to_eat * 1000);
	pthread_mutex_lock(&(philosopher->data->read_forks));
	philosopher->data->available_forks[r_fork] = 1;
	philosopher->data->available_forks[l_fork] = 1;
	pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->l_fork) - 1]));
	pthread_mutex_unlock(&(philosopher->data->forks[(philosopher->r_fork) - 1]));
	pthread_mutex_unlock(&(philosopher->data->read_forks));
	return ;
}

/*void	philo_sigle_eat(t_philo *philosopher)
{
	actual_time = check_alive(philosopher);
	print_get_fork(philosopher, actual_time);
}*/

void	philo_get_sleep(t_philo *philosophers)
{
	long long	actual_time_sleep;
	useconds_t	time_to_sleep;

	actual_time_sleep = check_alive(philosophers);
	if (actual_time_sleep == -1)
		return ;
	time_to_sleep = (useconds_t) philosophers->data->time_to_sleep;
	print_start_sleeping(philosophers, actual_time_sleep);
	usleep(time_to_sleep * 1000);
	return ;
}

/*Funcion que lee el is_alive de forma segura*/
int	check_running_simulation(t_philo *philosophers)
{
	int	is_alive;

	pthread_mutex_lock(&(philosophers->philo_mutex));
	is_alive = philosophers->is_alive;
	pthread_mutex_unlock(&(philosophers->philo_mutex));
	return (is_alive);
}

/*Rutina de cada filsofo*/
void	*routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *) arg;
	if (philosopher->id % 2 == 0)
        usleep(20000); // Duerme 1ms (o menos) para dar tiempo a los impares
	while (monitorize_finished(philosopher) != 1)
	{
		if (monitorize_finished(philosopher) != 1)
			philo_think(philosopher);
		if (monitorize_finished(philosopher) != 1)
			philo_eat(philosopher);
		if (monitorize_finished(philosopher) != 1)
			philo_get_sleep(philosopher);
	}
	return (NULL);
}

/*Rutina para un unico filosofo*/
void	*routine_single(void *arg)
{
	t_philo		*philosopher;
	long long	actual_time;

	philosopher = (t_philo *) arg;
	actual_time = check_alive(philosopher);
	print_get_fork(philosopher, actual_time);
	usleep(philosopher->data->time_to_die * 1000 + 1000);
	actual_time = check_alive(philosopher);
	if (actual_time != -1)
	{
		print_dead(philosopher, actual_time);
		pthread_mutex_lock(&(philosopher->data->sim));
		philosopher->data->finished = 1;
		pthread_mutex_unlock(&(philosopher->data->sim));
		pthread_mutex_lock(&(philosopher->philo_mutex));
		philosopher->is_alive = 0;
		pthread_mutex_unlock(&(philosopher->philo_mutex));
	}
	return (NULL);
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
		//printf("Se crea el filosofo numero %d\n", i + 1);
		philo->philosophers[i].id = i + 1;
		//printf("el tiempo para empezar a pensar es: %lld\n", first_think);
		philo->philosophers[i].time_last_eat = start_time;
		philo->philosophers[i].is_alive = 1;
		philo->philosophers[0].num_eat = 0;
		pthread_mutex_init(&(philo->philosophers[i].philo_mutex), NULL);
		pthread_create(&philo->philosophers[i].thread, NULL, routine, &philo->philosophers[i]);
		pthread_detach(philo->philosophers[i].thread);
		i++;
	}
	return ;
}

/*Funcion que verifica si todos los filosofos han comido la cantidad de veces necesaria*/
int	check_eat_all(t_philo_data *philo)
{
	int	num_to_eat;
	int	n_philo;
	int	i;
	
	num_to_eat = philo->number_to_eat;
	n_philo = philo->num_philo;
	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_lock(&(philo->philosophers[i].philo_mutex));
		if (philo->philosophers[i].num_eat < num_to_eat)
		{
			pthread_mutex_unlock(&(philo->philosophers[i].philo_mutex));
			return (0);
		}
		pthread_mutex_unlock(&(philo->philosophers[i].philo_mutex));
		i++;
	}
	return (1);
	
}

/*Funcion que moitoriza que la ejecucion aun no se debe terminar*/
void	monitor(t_philo_data *philo)
{
	int			n_philo;
	int			i;
	t_philo		*philosopher;
	useconds_t	time_to_eat;

	n_philo = philo->num_philo;
	while (1)
	{
		i = 0;
		while (i < n_philo)
		{
			if ((philo->number_to_eat != -1) && (check_eat_all(philo)))
			{
				pthread_mutex_lock(&(philo->sim));
				philo->finished = 1;
				pthread_mutex_unlock(&(philo->sim));
				time_to_eat = (useconds_t) philosopher->data->time_to_eat;
				usleep(time_to_eat * 1000);
				return ;
			}
			philosopher = &(philo->philosophers[i]);
			if (monitorize_finished(philosopher))
			{
				time_to_eat = (useconds_t) philosopher->data->time_to_eat;
				usleep(time_to_eat * 1000);
				return ;
			}
			if (check_alive(philosopher) == -1)
			{
				pthread_mutex_lock(&(philo->sim));
				philo->finished = 1;
				pthread_mutex_unlock(&(philo->sim));
				time_to_eat = (useconds_t) philosopher->data->time_to_eat;
				usleep(time_to_eat * 1000);
				return ;
			}
			i++;
		}
		usleep(100);
	}
	time_to_eat = (useconds_t) philosopher->data->time_to_eat;
	usleep(time_to_eat * 1000);
	return ;
}

/*Funcio que inicializa los forks*/
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

/*Funcion que inicia el proceo*/
void	philosophers(t_philo_data *philo, long long start_time)
{
	int				n;

	n = philo->num_philo;
	//forks_start(philo->forks, n);
	philosophers_start(philo, start_time);
}

/*Funcion que complementa la estructura tipo s_philo_data*/
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
	//printf("Termina la asignacion de argumentos\n");
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
		//printf("el id es %d\n", (int) (*d)->philosophers[i].id);
		(*d)->philosophers[i].data = (*d);
		(*d)->available_forks[i] = 1;
		i++;
	}
	(*d)->philosophers[0].l_fork = (*d)->num_philo;
	pthread_mutex_init(&((*d)->read_forks), NULL);
	pthread_mutex_init(&((*d)->msg), NULL);
	pthread_mutex_init(&((*d)->sim), NULL);
}

/*void	free_philo(t_philo_data *philo)
{
	
}*/

/*PHILOSOPHERS*/
int	main(int argc, char **argv)
{
	t_philo_data	*philo;
	long long		start_time;
	int				i;

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
	//printf("Termina la verificacion de argumentos\n");
	complete_philo_data(argc, argv, &philo);
	//printf("Termina de completar el philo_data\n");
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
	//free_philo(philo);
	return (EXIT_SUCCESS);
}
