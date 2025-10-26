/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:21:18 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 02:26:44 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "libft.h"
#include "env.h"

/**
 * @brief Updates an existing environment variable if it matches `name`.
 *
 * If the variable already exists, frees the old string and replaces it.
 *
 * @param envp Environment array
 * @param name Variable name
 * @param value Full "VAR=value" string
 * @return 1 if updated, 0 if not found
 */
static int	update_current_var(char **envp, const char *name, const char *value)
{
	int	i;
	int	name_len;

	if (!envp || !name || !value)
		return (0);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, name_len) && envp[i][name_len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(value);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Adds a new variable to the environment array.
 *
 * Allocates a new array, copies old entries, appends the new assignment,
 * frees the old array, and updates the pointer.
 *
 * @param envp Pointer to the environment array
 * @param assignment Full "VAR=value" string
 * @param count Number of existing entries
 * @return 0 on success, -1 on allocation error
 */
static int	add_new_var(char ***envp, const char *assignment, int count)
{
	char	**new_env;
	int		j;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (-1);
	j = 0;
	while (j < count)
	{
		new_env[j] = ft_strdup((*envp)[j]);
		j++;
	}
	new_env[count] = ft_strdup(assignment);
	new_env[count + 1] = NULL;
	free_envp(*envp);
	*envp = new_env;
	return (0);
}

/**
 * @brief Adds or updates an environment variable assignment.
 *
 * Takes a string of the form "VAR=value" and either updates the variable
 * in envp if it exists, or adds it if it doesn't.
 *
 * @param assignment The string containing the assignment (e.g. "PATH=/usr/bin")
 * @param envp A pointer to the environment array (char ***)
 * @return 0 on success, -1 on allocation error or invalid input
 */
int	export_assignment(char *assignment, char ***envp)
{
	char	*equal_sign;
	char	*name;
	int		count;

	if (!assignment || !envp)
		return (-1);
	equal_sign = ft_strchr(assignment, '=');
	if (!equal_sign)
		return (0);
	name = ft_substr(assignment, 0, equal_sign - assignment);
	if (!name)
		return (-1);
	count = 0;
	while ((*envp)[count])
		count++;
	if (update_current_var(*envp, name, assignment))
		return (free(name), 0);
	if (add_new_var(envp, assignment, count) == -1)
		return (free(name), -1);
	free(name);
	return (0);
}
