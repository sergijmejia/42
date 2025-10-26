/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:26:27 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 15:26:59 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica que un enviroment contiene PWD, SHLVL, _*/
int	check_env(char **envp)
{
	int		missing;
	int		i;

	missing = 3;
	if (envp == NULL)
		return (3);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			missing--;
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			missing--;
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			missing--;
		if (missing == 0)
			return (0);
		i++;
	}
	return (missing);
}
