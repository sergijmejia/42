/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:43:11 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:01:46 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "var_utils.h"
#include "minishell_exec.h"
#include "env.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Checks if a variable name is valid.
 *
 * - Must start with a letter or '_'
 * - Can contain letters, numbers, or '_'
 *
 * @param name Variable name to check
 * @return 1 if valid, 0 otherwise
 */
int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Inserts a new temporary variable into the list.
 *
 * Ownership of name and value is transferred to the list.
 *
 * @param temp_vars Pointer to the head of the temporary variable list
 * @param name Name of the variable
 * @param value Value of the variable
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
 * @brief Counts total variables in envp array.
 *
 * @param envp Environment array
 * @return Number of variables
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
 * @brief Fills preallocated array with envp variables.
 *
 * @param all_vars Preallocated array
 * @param envp Environment array
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
