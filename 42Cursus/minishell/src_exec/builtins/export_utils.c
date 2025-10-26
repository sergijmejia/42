/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:43:11 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/21 23:43:16 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "var_utils.h"
#include "minishell_exec.h"
#include "env.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Inserts a new temporary variable into the list.
 *
 * Allocates a new node with name and value, and adds it
 * at the front of temp_vars list.
 *
 * @param temp_vars Pointer to the head of temporary variable list
 * @param name Name of the variable (will be owned by the list)
 * @param value Value of the variable (will be owned by the list)
 */
void	insert_temp_var(t_temp_lst_exec **temp_vars,
							char *name, char *value)
{
	t_temp_lst_exec	*new;

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
 * @brief Handles the addition or export of shell variables.
 *
 * Implements Bash-like behavior for the `export` builtin:
 * - When called as `export VAR=value`, the variable is added or updated in the
 *   global environment (`envp`).
 * - When called as `export VAR` (without '='), the function promotes the variable
 *   from a local scope (either `temp_vars` or `parser_tmp_vars`) to the environment.
 *   If the variable does not exist in any local scope, an empty variable is
 *   created in the environment.
 *
 * Promotion means:
 *   1. The variable's value is copied from the local list to `envp`.
 *   2. The variable is removed from both the temporary (`temp_vars`) and parser
 *      (`parser_tmp_vars`) variable lists, to avoid duplicates.
 *
 * @param temp_vars Pointer to the list of temporary (local) shell variables.
 * @param arg The argument string, e.g. "VAR=value" or "VAR".
 * @param envp Pointer to the environment array to update.
 * @param parser_tmp_vars Pointer to the parser's local variable list.
 *
 * @note This function ensures consistent synchronization between local,
 *       parser-level, and environment variable scopes.
 */
void	add_var(t_temp_lst_exec **temp_vars, char *arg,
              char ***envp, t_list **parser_tmp_vars)
{
	char	*eq;
	char	*name;
	char	*value;
	char 	*tmp_val;

	if (!arg || !*arg)
		return ;
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		// Look in the temp_vars (local shell)
		tmp_val = get_temp_var_value(*temp_vars, arg);
		if (tmp_val)
		{
			update_env_var(envp, arg, tmp_val);
			remove_local_var(temp_vars, arg);
			remove_parser_tmp_var(parser_tmp_vars, arg);
			return;
		}
		// Look in the parser_tmp_vars
		tmp_val = get_parser_tmp_var_value(*parser_tmp_vars, arg);
		if (tmp_val)
		{
			update_env_var(envp, arg, tmp_val);
			remove_parser_tmp_var(parser_tmp_vars, arg);
			return;
		}
		// If cannot find it then create it new
		if (!get_env_val(*envp, arg))
			export_assignment(arg, envp);
		return;
	}
	name = ft_substr(arg, 0, eq - arg);
	if (!name)
		return ;
	value = ft_strdup(eq + 1);
	if (!value)
	{
		free(name);
		return ;
	}
	// Si ya existe, actualiza; si no, inserta nueva
	if (get_env_val(*envp, name))
		update_env_var(envp, name, value);
	else
	{
		insert_temp_var(temp_vars, name, value);
		export_assignment(arg, envp);
	}
	free(name);
	free(value);
}

/**
 * @brief Counts total variables in temp_vars and envp.
 *
 * @param envp Environment array
 * @param temp_vars Temporary variable list
 * @return Total count of variables
 */
int	count_vars(char **envp, t_temp_lst_exec *temp_vars)
{
	int				count;
	int				i;
	t_temp_lst_exec	*cur;

	count = 0;
	cur = temp_vars;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	i = 0;
	while (envp[i])
		i++;
	count += i;
	return (count);
}

/**
 * @brief Fills all_vars array with temp_vars and envp contents.
 *
 * @param all_vars Preallocated array
 * @param envp Environment array
 * @param temp_vars Temporary variable list
 * @return Number of entries filled
 */
int	fill_all_vars(char **all_vars, char **envp,
						t_temp_lst_exec *temp_vars)
{
	int				i;
	int				j;
	t_temp_lst_exec	*cur;
	char			*tmp;

	i = 0;
	cur = temp_vars;
	while (cur)
	{
		if (cur->value)
		{
			tmp = ft_strjoin(cur->name, "=");
			all_vars[i] = ft_strjoin(tmp, cur->value);
			free(tmp);
		}
		else
			all_vars[i] = ft_strdup(cur->name);
		i++;
		cur = cur->next;
	}
	j = -1;
	while (envp[++j])
		all_vars[i++] = ft_strdup(envp[j]);
	all_vars[i] = NULL;
	return (i);
}
