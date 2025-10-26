/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti@student.42barcelon>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:00:00 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 10:26:17 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <readline/history.h>
#include <stdio.h>

/**
 * @brief Builtin 'history': prints the command history with numbering.
 *
 * @return Exit status (0 = success)
 */
int	builtin_history(void)
{
	int			i;
	HIST_ENTRY	**hist_list;

	hist_list = history_list();
	if (!hist_list)
		return (0);
	i = 0;
	while (hist_list[i])
	{
		printf("%5d  %s\n", i + 1, hist_list[i]->line);
		i++;
	}
	return (0);
}
