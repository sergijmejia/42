/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:00:32 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/26 12:00:00 by rafaguti         ###   ########.fr       */
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
static char *var_to_string(t_temp_lst_exec *var)
{
    char *tmp;
    char *res;

    if (!var)
        return NULL;
    tmp = ft_strjoin(var->name, "=");
    if (!tmp)
        return NULL;
    res = ft_strjoin(tmp, var->value);
    free(tmp);
    if (!res)
        return NULL;
    return res;
}

/**
 * @brief Counts the number of nodes in temp_vars list.
 *
 * @param temp_vars Head of the list
 * @return Number of nodes
 */
static int count_temp_vars(t_temp_lst_exec *temp_vars)
{
    int count = 0;

    while (temp_vars)
    {
        count++;
        temp_vars = temp_vars->next;
    }
    return count;
}

/**
 * @brief Counts the number of strings in envp array.
 *
 * @param envp Environment array
 * @return Number of strings
 */
static int count_env(char **envp)
{
    int count = 0;

    if (!envp)
        return 0;
    while (envp[count])
        count++;
    return count;
}

/**
 * @brief Copies temp_vars list into an envp array starting at index start.
 *
 * Returns 0 on success, 1 on allocation failure.
 *
 * @param temp_vars Head of the temp_vars list
 * @param new_env Array to store the strings
 * @param start Pointer to index to start writing in new_env
 * @return int 0 = ok, 1 = error
 */
static int copy_temp_vars(t_temp_lst_exec *temp_vars, char **new_env, int *start)
{
    char *str;

    while (temp_vars)
    {
        str = var_to_string(temp_vars);
        if (!str)
            return 1; // fallo
        new_env[*start] = str;
        (*start)++;
        temp_vars = temp_vars->next;
    }
    return 0; // todo ok
}

/**
 * @brief Builds a new envp array from temp_vars and existing envp.
 *
 * Handles allocation failures safely, liberando memoria parcialmente creada.
 *
 * @param temp_vars Linked list of temporary variables
 * @param envp Existing environment array
 * @return Newly allocated envp array or NULL on failure
 */
char **build_envp(t_temp_lst_exec *temp_vars, char **envp)
{
    char **new_env;
    int total_count;
    int i = 0, j = 0;

    total_count = count_temp_vars(temp_vars) + count_env(envp);
    new_env = malloc(sizeof(char *) * (total_count + 1));
    if (!new_env)
        return NULL;

    if (copy_temp_vars(temp_vars, new_env, &i))
    {
        while (--i >= 0)
            free(new_env[i]);
        free(new_env);
        return NULL;
    }

    if (envp)
    {
        j = 0;
        while (envp[j])
        {
            new_env[i] = ft_strdup(envp[j]);
            if (!new_env[i])
            {
                while (--i >= 0)
                    free(new_env[i]);
                free(new_env);
                return NULL;
            }
            i++;
            j++;
        }
    }

    new_env[i] = NULL;
    return new_env;
}
