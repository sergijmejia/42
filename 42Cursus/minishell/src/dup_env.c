/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:04:44 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/07 15:05:03 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **dup_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = (char **) malloc ((i + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (env[i] == NULL)
			return(free_str(env));
		i++;
	}
	env[i] = NULL;
	return (env);
}
