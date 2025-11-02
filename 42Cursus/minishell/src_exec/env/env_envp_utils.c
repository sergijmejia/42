/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:17:28 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/29 00:05:46 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "libft.h"
#include "utils.h"

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
        {
            while(--i >= 0)
                free(new_env[i]);
            free(new_env);
            return (NULL);
        }
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

/**
 * @brief Safe string join of three strings.
 */
static char *ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
    char    *tmp;
    char    *res;

    tmp = ft_strjoin(s1, s2);
    if (!tmp)
        return (NULL);
    res = ft_strjoin(tmp, s3);
    free(tmp);
    return (res);
}

/**
 * @brief Updates or creates an environment variable in envp (name=value)
 *
 * - If the variable exists, replaces it safely.
 * - If not, allocates a new env array and appends it.
 * - Ensures no leaks or dangling pointers.
 */
int update_env_var(char ***envp, const char *name, const char *value)
{
    int i;
    int j;
    size_t len;
    char *new_entry;
    char **new_env;

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
    // Variable no existe, crear nuevo array duplicando
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (-1);
    j = 0;
    while (j < i)
    {
        new_env[j] = ft_strdup((*envp)[j]);
        if (!new_env[j])
        {
		    while (--j >= 0)
                free(new_env[j]);
            free(new_env);
            return (-1);
        }
        j++;
    }
    new_env[i] = ft_strjoin3(name, "=", value);
    if (!new_env[i])
    {
		while (--j >= 0)
			free(new_env[j]);
		free(new_env);
		return (-1);
    }
    new_env[i + 1] = NULL;

    free_envp(*envp);
    *envp = new_env;

    return (0);
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
