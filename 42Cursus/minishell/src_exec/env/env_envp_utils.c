/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:17:28 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/21 22:18:43 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "libft.h"
#include "utils.h"

/**
 * @brief Frees an envp array using ft_free_split.
 *
 * @param envp Array to free
 */
void	free_envp(char **envp)
{
	if (envp)
		free_split(envp);
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
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

static int update_or_append_var(char ***envp, const char *new_var, const char *name)
{
    if (!envp || !new_var || !name)
        return 1;

    size_t len = ft_strlen(name);
    int i = 0;

    // Buscar si la variable existe
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
        {
            char *tmp = ft_strdup(new_var);  // duplicamos para no tocar el original
            if (!tmp)
                return 1;
            free((*envp)[i]);               // liberamos solo el string viejo
            (*envp)[i] = tmp;
            return 0;                        // éxito
        }
        i++;
    }

    // No existe: crear nuevo array con i strings + new_var + NULL
    char **new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return 1;

    for (int j = 0; j < i; j++)
    {
        new_env[j] = ft_strdup((*envp)[j]);
        if (!new_env[j])
        {
            while (--j >= 0)
                free(new_env[j]);
            free(new_env);
            return 1;
        }
    }

    new_env[i] = ft_strdup(new_var);
    if (!new_env[i])
    {
        while (--i >= 0)
            free(new_env[i]);
        free(new_env);
        return 1;
    }

    new_env[i + 1] = NULL;

    free(*envp);   // liberamos solo el array viejo, strings ya duplicados
    *envp = new_env;
    return 0;
}

/**
 * @brief Updates or creates an environment variable in envp (name=value)
 *
 * - If the variable exists, replaces it safely.
 * - If not, allocates a new env array and appends it.
 * - Ensures no leaks or dangling pointers.
 */
void update_env_var(char ***envp, const char *name, const char *value)
{
    if (!envp || !name || !value)
        return;

    char *tmp = ft_strjoin(name, "=");
    if (!tmp)
        return;

    char *new_var = ft_strjoin(tmp, value);
    free(tmp);
    if (!new_var)
        return;

    // Actualiza o agrega: ahora siempre duplica los strings, nunca toca punteros compartidos
    if (update_or_append_var(envp, new_var, name) != 0)
    {
        free(new_var);
        return;
    }

    free(new_var);
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
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
	return (NULL);
}
