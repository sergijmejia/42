/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:58:54 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/03 19:58:55 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "libft.h"
#include "env.h"
#include "utils.h"

/**
 * @brief Safely joins three strings into a new allocated one.
 *
 * Creates a new string equivalent to s1 + s2 + s3.
 * Returns NULL if any allocation fails.
 *
 * @param s1 First string
 * @param s2 Second string
 * @param s3 Third string
 * @return A new concatenated string or NULL on failure
 */
static char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

/**
 * @brief Appends a new variable to envp when it does not exist.
 *
 * Allocates a new environment array, duplicates existing entries,
 * appends the new "name=value" pair, frees the old envp, and replaces it.
 *
 * @param envp Pointer to the environment array
 * @param name Variable name
 * @param value Variable value
 * @param index Number of existing entries in envp
 * @return 0 on success, -1 on allocation failure
 */
static int	append_env_var(char ***envp, const char *name,
	const char *value, int index)
{
	int		j;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (index + 2));
	if (!new_env)
		return (-1);
	j = 0;
	while (j < index)
	{
		new_env[j] = ft_strdup((*envp)[j]);
		if (!new_env[j])
			return (free_partial_env(new_env, j), -1);
		j++;
	}
	new_env[index] = ft_strjoin3(name, "=", value);
	if (!new_env[index])
		return (free_partial_env(new_env, j), -1);
	new_env[index + 1] = NULL;
	free_envp(*envp);
	*envp = new_env;
	return (0);
}

/**
 * @brief Updates or creates an environment variable in envp (name=value)
 *
 * - If the variable exists, replaces it safely.
 * - If not, allocates a new env array and appends it.
 * - Ensures no leaks or dangling pointers.
 *
 * @param envp Pointer to the environment array
 * @param name Variable name
 * @param value Variable value
 * @return 0 on success, -1 on allocation failure
 */
int	update_env_var(char ***envp, const char *name, const char *value)
{
	int		i;
	size_t	len;
	char	*new_entry;

	if (!envp || !name || !value)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
		{
			new_entry = ft_strjoin3(name, "=", value);
			if (!new_entry)
				return (-1);
			free((*envp)[i]);
			(*envp)[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (append_env_var(envp, name, value, i));
}
