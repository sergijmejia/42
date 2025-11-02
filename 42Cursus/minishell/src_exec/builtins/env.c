/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:41:22 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/28 02:55:07 by rafaguti         ###   ########.fr       */
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
    int count, j;
    char **new_env;

    if (!name || !envp || !*envp)
        return (-1);
    count = 0;
    for (int i = 0; (*envp)[i]; i++)
        if (!(ft_strncmp((*envp)[i], name, ft_strlen(name)) == 0 && (*envp)[i][ft_strlen(name)] == '='))
            count++;
    new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return (-1);
    j = 0;
    for (int i = 0; (*envp)[i]; i++)
    {
        if (ft_strncmp((*envp)[i], name, ft_strlen(name)) == 0 && (*envp)[i][ft_strlen(name)] == '=')
        {
            free((*envp)[i]);
            continue;
        }
        new_env[j++] = (*envp)[i];
    }
    new_env[j] = NULL;
    free(*envp);
    *envp = new_env;
    return (0);
}
