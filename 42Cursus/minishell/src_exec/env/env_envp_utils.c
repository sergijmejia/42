/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:17:28 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:54:02 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "libft.h"
#include "env.h"
#include "utils.h"

/**
 * @brief Frees a partially allocated env array and returns NULL.
 *
 * @param env The partially allocated environment array
 * @param filled The number of valid entries already allocated
 * @return Always returns NULL for convenience in error returns
 */
void	*free_partial_env(char **env, int filled)
{
	while (--filled >= 0)
		free(env[filled]);
	free(env);
	return (NULL);
}

/**
 * @brief Frees an envp array safely and nullifies its elements
 *
 * @param envp Array to free
 */
void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
}

/**
 * @brief Clones an envp array.
 *
 * Allocates a new array and duplicates each string.
 *
 * @param envp The original envp array
 * @return A new duplicated envp array, or NULL if allocation fails
 */
char	**clone_envp(char **envp)
{
	int		count;
	int		i;
	char	**new_env;

	if (!envp)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
			return (free_partial_env(new_env, i));
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

/**
 * @brief Retrieves the value of an environment variable from envp only
 */
char	*get_env_val(char **envp, const char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
