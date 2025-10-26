/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:00:32 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 11:47:37 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "libft.h"

/**
 * @brief Converts a temp variable into "NAME=VALUE" string.
 *
 * Uses ft_strjoin safely, freeing temporary memory if needed.
 *
 * @param var Temporary variable
 * @return Newly allocated string "NAME=VALUE" or NULL
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
	if (!res)
		return (NULL);
	return (res);
}

/**
 * @brief Counts the number of nodes in temp_vars list.
 *
 * @param temp_vars Head of the list
 * @return Number of nodes
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
 * @brief Counts the number of strings in envp array.
 *
 * @param envp Environment array
 * @return Number of strings
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
 * @brief Copies temp_vars list into an envp array starting at index start.
 *
 * Frees strings if allocation fails to avoid leaks.
 *
 * @param temp_vars Head of the temp_vars list
 * @param new_env Array to store the strings
 * @param start Pointer to index to start writing in new_env
 */
static void	copy_temp_vars(t_temp_lst_exec *temp_vars,
		char **new_env, int *start)
{
	char	*str;

	while (temp_vars)
	{
		str = var_to_string(temp_vars);
		if (!str)
			break ;
		new_env[*start] = str;
		(*start)++;
		temp_vars = temp_vars->next;
	}
}

/**
 * @brief Builds a new envp array from temp_vars and existing envp.
 *
 * @param temp_vars Linked list of temporary variables
 * @param envp Existing environment array
 * @return Newly allocated envp array
 */
char	**build_envp(t_temp_lst_exec *temp_vars, char **envp)
{
	char	**new_env;
	int		total_count;
	int		i;
	int		j;

	total_count = count_env(envp) + count_temp_vars(temp_vars);
	new_env = malloc(sizeof(char *) * (total_count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	copy_temp_vars(temp_vars, new_env, &i);
	if (envp)
	{
		j = 0;
		while (envp[j])
			new_env[i++] = ft_strdup(envp[j++]);
	}
	new_env[total_count] = NULL;
	return (new_env);
}
