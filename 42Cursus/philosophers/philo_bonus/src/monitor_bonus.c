/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:17:31 by smejia-a          #+#    #+#             */
/*   Updated: 2025/11/24 11:56:20 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_pid(pid_t *pids, int size, pid_t pid_finished)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pids[i] == pid_finished)
			pids[i] = 0;
		i++;
	}
}

static int	should_stop(int status, int *finished, int total_philo)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
			return (0);
		(*finished)++;
		if (*finished == total_philo)
			return (0);
		return (-1);
	}
	return (1);
}

int	monitor(t_philo_data *philo, pid_t *pids)
{
	int		status;
	int		finished;
	int		stop;
	pid_t	pid_finished;

	finished = 0;
	while (1)
	{
		pid_finished = waitpid(-1, &status, WNOHANG);
		if (pid_finished < 0)
			return (0);
		if (pid_finished == 0)
			usleep(100);
		else
		{
			clean_pid(pids, philo->num_philo, pid_finished);
			stop = should_stop(status, &finished, philo->num_philo);
			if (stop >= 0)
				return (stop);
		}
	}
	return (0);
}
