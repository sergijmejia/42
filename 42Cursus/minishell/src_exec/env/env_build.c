/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:00:00 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:44:27 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "libft.h"
#include "minishell_exec.h"

/**
 * @brief Converts a temporary variable to a "NAME=VALUE" string.
 *
 * @param var Temporary variable.
 * @return Allocated string or NULL on failure.
 */
static char	*var_to_string(t_temp_lst_exec *var)
{
	char	*tmp;
	char	*res;

	if (!var)
		return (NULL);
	tmp = ft_strjoin(var->name, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, var->value);
	free(tmp);
	return (res);
}

/**
 * @brief Counts the nodes in a linked list.
 *
 * @param temp_vars Head of list.
 * @return Number of nodes.
 */
static int	count_temp_vars(t_temp_lst_exec *temp_vars)
{
	int	count;

	count = 0;
	while (temp_vars)
	{
		count++;
		temp_vars = temp_vars->next;
	}
	return (count);
}

/**
 * @brief Counts the strings in an envp array.
 *
 * @param envp Array.
 * @return Number of strings.
 */
static int	count_env(char **envp)
{
	int	count;

	count = 0;
	if (!envp)
		return (0);
	while (envp[count])
		count++;
	return (count);
}

/**
 * @brief Copies environment variables from envp to new_env.
 *
 * @param new_env Pointer to the destination array of strings.
 * @param envp Array of environment variable strings to copy.
 * @param i Current index in new_env where copying should start.
 * @return The next available index in new_env, or -1 on allocation failure.
 */
static int	copy_envp_to_new(char **new_env, char **envp, int i)
{
	int	j;

	j = 0;
	while (envp && envp[j])
	{
		new_env[i] = ft_strdup(envp[j]);
		if (!new_env[i])
			return (free_partial_env(new_env, i), -1);
		i++;
		j++;
	}
	return (i);
}

/**
 * @brief Builds a combined environment array from temporary variables and envp.
 *
 * This function concatenates environment variables stored in a temporary
 * linked list with those provided in envp, allocating memory for a new
 * null-terminated array of strings.
 *
 * @param temp_vars Pointer to a linked list of temporary environment variables.
 * @param envp Array of environment variable strings (the original environment).
 * @return A newly allocated array of environment array, or NULL on failure.
 */
char	**build_envp(t_temp_lst_exec *temp_vars, char **envp)
{
	char	**new_env;
	int		total;
	int		i;

	total = count_temp_vars(temp_vars) + count_env(envp);
	new_env = malloc(sizeof(char *) * (total + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (temp_vars)
	{
		new_env[i] = var_to_string(temp_vars);
		if (!new_env[i])
			return (free_partial_env(new_env, i), NULL);
		i++;
		temp_vars = temp_vars->next;
	}
	i = copy_envp_to_new(new_env, envp, i);
	if (i == -1)
		return (NULL);
	new_env[i] = NULL;
	return (new_env);
}
