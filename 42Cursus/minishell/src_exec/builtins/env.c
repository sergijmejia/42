/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:41:22 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 12:21:09 by rafaguti         ###   ########.fr       */
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
 * @brief Duplicates a single env string safely into dst[j].
 *
 * @param dst Destination array
 * @param j Index in destination array
 * @param src_string Source string to duplicate
 * @return 0 on success, -1 on allocation failure
 */
static int	duplicate_env_string(char **dst, int j, const char *src_string)
{
	dst[j] = ft_strdup(src_string);
	if (!dst[j])
		return (-1);
	return (0);
}

/**
 * @brief Copies all strings from src to dst except those matching the given name.
 *
 * Allocates new strings for dst. Frees strings from src regardless of whether
 * they are copied or not. Skips all occurrences of "name=" in src.
 *
 * @param src Source array of strings (null-terminated).
 * @param dst Destination array, already allocated with enough space.
 * @param name Variable name to exclude from copying.
 * @return 0 on success, -1 on memory allocation failure.
 */
static int	copy_env_except_safe(char **src, char **dst, const char *name)
{
	int	i;
	int	j;
	size_t	len;

	i = -1;
	j = 0;
	len = ft_strlen(name);
	while (src[++i])
	{
		// Omitir TODAS las coincidencias exactas de name=
		if (ft_strncmp(src[i], name, len) == 0 && src[i][len] == '=')
		{
			free(src[i]);
			continue ;
		}
		if (duplicate_env_string(dst, j, src[i]) == -1)
		{
			while (j > 0)
				free(dst[--j]);
			free(dst);
			return (-1);
		}
		free(src[i]);
		j++;
	}
	dst[j] = NULL;
	return (0);
}

/**
 * @brief Removes all occurrences of a variable from the environment array.
 *
 * Allocates a new environment array, copies all variables except the ones
 * matching the given name, and frees the old array.
 *
 * Example:
 *   unset_assignment("VAR", &envp);
 *   -> removes all "VAR=..." entries from envp.
 *
 * @param name Variable name to remove.
 * @param envp Pointer to the environment array to modify.
 * @return 0 on success, -1 on error (e.g., allocation failure or invalid input).
 */
int	unset_assignment(const char *name, char ***envp)
{
	int		count;
	char	**new_env;

	if (!name || !envp || !*envp)
		return (-1);
	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (-1);
	if (copy_env_except_safe(*envp, new_env, name) == -1)
	{
		free(new_env);
		*envp = NULL;
		return (-1);
	}
	free(*envp);
	*envp = new_env;
	return (0);
}
