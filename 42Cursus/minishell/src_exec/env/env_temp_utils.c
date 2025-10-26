/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_temp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:16:56 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/21 22:18:07 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "libft.h"
#include "utils.h"

/**
 * @brief Frees a temporary variable list.
 *
 * @param temp_vars Pointer to the head of the list
 */
void	free_temp_vars(t_temp_lst_exec **temp_vars)
{
	t_temp_lst_exec	*tmp;
	t_temp_lst_exec	*next;

	if (!temp_vars)
		return ;
	tmp = *temp_vars;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*temp_vars = NULL;
}

/**
 * @brief Adds a new temporary variable to the list.
 *
 * @param temp_vars Pointer to the head of the list
 * @param name Variable name
 * @param value Variable value
 */
void	add_temp_var(t_temp_lst_exec **temp_vars, char *name, char *value)
{
	t_temp_lst_exec	*new_var;

	if (!temp_vars || !name || !value)
		return ;
	new_var = malloc(sizeof(t_temp_lst_exec));
	if (!new_var)
		return ;
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	new_var->next = *temp_vars;
	*temp_vars = new_var;
}

/**
 * @brief Adds a temporary variable to the parser's list.
 *
 * @param parser_tmp_var Pointer to the parser's temporary variable list
 * @param name Name of the variable
 * @param value Value of the variable
 */
void	add_parser_tmp_var(t_list **parser_tmp_var,
		const char *name, const char *value)
{
	t_temp_lst	*entry;
	t_list		*node;

	if (!parser_tmp_var || !name)
		return ;
	entry = malloc(sizeof(t_temp_lst));
	if (!entry)
		return ;
	entry->name = ft_strdup(name);
	entry->value = ft_strdup(value);
	node = ft_lstnew(entry);
	if (!node)
	{
		free(entry->name);
		free(entry->value);
		free(entry);
		return ;
	}
	ft_lstadd_front(parser_tmp_var, node);
}
