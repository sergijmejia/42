/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:43:11 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/01 12:53:32 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "var_utils.h"
#include "minishell_exec.h"
#include "env.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Comprueba si name es un identificador válido de variable.
 *
 * - Debe empezar por letra o '_'
 * - Puede contener letras, números o '_'
 *
 * @param name Nombre a comprobar
 * @return 1 si es válido, 0 si no
 */
static int is_valid_var_name(const char *name)
{
    int i;

    if (!name || !*name)
        return 0;
    if (!isalpha(name[0]) && name[0] != '_')
        return 0;
    i = 1;
    while (name[i])
    {
        if (!isalnum(name[i]) && name[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

/**
 * @brief Inserts a new temporary variable into the list.
 *
 * Ownership of name and value is transferred to the list.
 * On malloc failure, both are freed.
 *
 * @param temp_vars Pointer to the head of temporary variable list
 * @param name Name of the variable (will be owned by the list)
 * @param value Value of the variable (will be owned by the list)
 */
void	insert_temp_var(t_temp_lst_exec **temp_vars,
							char *name, char *value)
{
	t_temp_lst_exec	*new;

	if (!name || !value)
		return ;
	new = malloc(sizeof(t_temp_lst_exec));
	if (!new)
	{
		free(name);
		free(value);
		return ;
	}
	new->name = name;
	new->value = value;
	new->next = *temp_vars;
	*temp_vars = new;
}

/**
 * @brief Handles the addition or export of shell variables safely.
 *
 * Ownership rules:
 * - If inserting into temp_vars, ownership of name/value is transferred.
 * - Otherwise, name/value are freed at the end of the function.
 */
void	add_var(t_temp_lst_exec **temp_vars, char *arg,
		char ***envp, t_list **parser_tmp_vars)
{
    char *eq;
    char *name;
    char *value;
    char *tmp_val;

    name = NULL;
    value = NULL;
    if (!arg || !*arg)
        return ;

    eq = ft_strchr(arg, '=');
    if (!eq)
    {
        /* Promoción desde temp_vars */
        tmp_val = get_temp_var_value(*temp_vars, arg);
        if (tmp_val)
        {
            if (is_valid_var_name(arg))
                update_env_var(envp, arg, tmp_val);
            remove_local_var(temp_vars, arg);
            remove_parser_tmp_var(parser_tmp_vars, arg);
            return ;
        }
        tmp_val = get_parser_tmp_var_value(*parser_tmp_vars, arg);
        if (tmp_val)
        {
            if (is_valid_var_name(arg))
                update_env_var(envp, arg, tmp_val);
            remove_parser_tmp_var(parser_tmp_vars, arg);
            return ;
        }
        if (!get_env_val(*envp, arg) && is_valid_var_name(arg))
            export_assignment(arg, envp);
        return ;
    }

    /* Separar nombre y valor */
    name = ft_substr(arg, 0, eq - arg);
    if (!name)
        return ;
    value = ft_strdup(eq + 1);
    if (!value)
    {
        free(name);
        return ;
    }

    /* Validar nombre */
    if (!is_valid_var_name(name))
    {
        fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", name);
        free(name);
        free(value);
        return ;
    }

    /* Insertar o actualizar */
    if (get_env_val(*envp, name))
    {
        update_env_var(envp, name, value);
        free(name);
        free(value);
    }
	else
	{
		// Transfer ownership to temp_vars
		insert_temp_var(temp_vars, name, value);
		export_assignment(arg, envp);
		// name/value ownership transferred, do not free
	}
}

/**
 * @brief Counts total variables in temp_vars and envp.
 *
 * @param envp Environment array
 * @return Total count of variables
 */
int	count_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/**
 * @brief Fills all_vars array with temp_vars and envp contents.
 *
 * @param all_vars Preallocated array
 * @param envp Environment array
 * @param temp_vars Temporary variable list
 * @return Number of entries filled
 */
int	fill_all_vars(char **all_vars, char **envp)
{
	int				i;

	i = 0;
	while (envp[i])
	{
		all_vars[i] = ft_strdup(envp[i]);
		i++;
	}
	all_vars[i] = NULL;
	return (i);
}
