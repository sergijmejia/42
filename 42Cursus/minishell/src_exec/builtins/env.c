/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:41:22 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 16:07:35 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Prints all environment variables except "_=".
 *
 * @param envp Environment array
 * @return Exit status (0 on success, 1 if envp is NULL)
 */
int	builtin_env(char **envp)
{
	int	i;

	if (!envp)
		return (1);
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "_=", 2) != 0)
			ft_putendl_fd(envp[i], 1);
	ft_putendl_fd("_=/usr/bin/env", 1);
	return (0);
}

/**
 * @brief Counts how many env vars remain after removing 'name'.
 */
static int	count_env_vars_to_remove(const char *name, char **envp)
{
	int		count;
	int		i;
	size_t	len;

	count = 0;
	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '='))
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief Builds a new env array without the given variable.
 */
static void	rebuild_env_without_var(char **new_env,
	const char *name, char **envp)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			i++;
			continue ;
		}
		new_env[j++] = envp[i++];
	}
	new_env[j] = NULL;
}

/**
 * @brief Removes all occurrences of a variable from the environment array.
 *
 * Allocates a new environment array excluding any variable that matches `name`.
 * Frees the old environment and updates the pointer.
 *
 * @return 0 on success, -1 on error.
 */
int	unset_assignment(const char *name, char ***envp)
{
	int		count;
	char	**new_env;

	if (!name || !envp || !*envp)
		return (-1);
	count = count_env_vars_to_remove(name, *envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (-1);
	rebuild_env_without_var(new_env, name, *envp);
	free(*envp);
	*envp = new_env;
	return (0);
}
