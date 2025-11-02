/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:00:00 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/29 12:20:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
 * @brief Frees a partially filled env array in case of malloc failure.
 *
 * @param env Array to free.
 * @param filled Number of allocated elements.
 */
static void	free_partial_env(char **env, int filled)
{
	while (--filled >= 0)
		free(env[filled]);
	free(env);
}

/**
 * @brief Counts the nodes in a linked list.
 *
 * @param temp_vars Head of list.
 * @return Number of nodes.
 */
static int	count_temp_vars(t_temp_lst_exec *temp_vars)
{
	int	count = 0;

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
	int	count = 0;

	if (!envp)
		return (0);
	while (envp[count])
		count++;
	return (count);
}

/**
 * @brief Builds a new envp array from temp_vars and existing envp.
 *
 * Each element is newly allocated. Returns NULL on failure.
 *
 * @param temp_vars Linked list of temporary variables.
 * @param envp Existing environment array.
 * @return Newly allocated envp array or NULL.
 */
char	**build_envp(t_temp_lst_exec *temp_vars, char **envp)
{
	char	**new_env;
	int		total;
	int		i;
	int		j;

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
	j = 0;
	while (envp && envp[j])
	{
		new_env[i] = ft_strdup(envp[j]);
		if (!new_env[i])
			return (free_partial_env(new_env, i), NULL);
		i++;
		j++;
	}
	new_env[i] = NULL;
	return (new_env);
}