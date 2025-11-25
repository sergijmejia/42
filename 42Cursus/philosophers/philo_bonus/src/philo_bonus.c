/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:10:58 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/24 12:02:35 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philosophers_end(t_philo_data *philo, pid_t *pids, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pids[i] != 0)
			kill(pids[i], SIGKILL);
		i++;
	}
	sem_unlink("/p_forks");
	sem_unlink("/p_print");
	sem_unlink("/p_room");
	free(pids);
	free(philo);
	return ;
}

static pid_t	*philosophers_start_loop(t_philo_data *philo, pid_t *pid, int i)
{
	pid_t	aux;
	int		exit_status;

	aux = fork();
	if (aux == -1)
	{
		philosophers_end(philo, pid, i);
		return (NULL);
	}
	if (aux == 0)
	{
		exit_status = start_routine(philo, i + 1);
		if (exit_status)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		pid[i] = aux;
	return (pid);
}

static pid_t	*philosophers_start(t_philo_data *philo)
{
	pid_t	*pid;
	int		i;

	i = 0;
	pid = (pid_t *) malloc ((philo->num_philo) * sizeof(pid_t));
	if (pid == NULL)
		return (NULL);
	while (i < philo->num_philo)
	{
		if (philosophers_start_loop(philo, pid, i) == NULL)
			return (NULL);
		i++;
	}
	return (pid);
}

int	main(int argc, char **argv)
{
	t_philo_data	*philo;
	long long		start_time;
	pid_t			*pids;

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
	pids = philosophers_start(philo);
	if (pids == NULL)
		return (EXIT_FAILURE);
	monitor(philo, pids);
	philosophers_end(philo, pids, philo->num_philo);
	return (EXIT_SUCCESS);
}
