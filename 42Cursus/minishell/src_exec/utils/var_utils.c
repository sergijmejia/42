/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:41:59 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/26 16:42:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "minishell_exec.h"

/**
 * @brief Removes all nodes with the given name from the temporary variable list.
 *
 * Iterates through the linked list of local variables (t_temp_lst_exec) and
 * safely frees any node whose name matches the provided variable name.
 *
 * @param temp_vars Pointer to the head of the temporary variable list.
 * @param name Name of the variable to remove.
 */
void    remove_local_var(t_temp_lst_exec **temp_vars, const char *name)
{
	t_temp_lst_exec	*curr;
	t_temp_lst_exec	*prev;

	if (!temp_vars || !*temp_vars || !name)
		return ;
	curr = *temp_vars;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->name, name, ft_strlen(name) + 1) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*temp_vars = curr->next; // era el primero
			free(curr->name);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

/**
 * @brief Removes all nodes with the given name from the parser's temporary variable list.
 *
 * Iterates through the linked list of parser variables (t_list containing t_pair)
 * and safely frees any node whose name matches the provided variable name.
 *
 * @param parser_tmp_var Pointer to the head of the parser's temporary variable list.
 * @param name Name of the variable to remove.
 */
void remove_parser_tmp_var(t_list **parser_tmp_var, char *name)
{
    t_list *prev = NULL;
    t_list *curr = *parser_tmp_var;

    if (!parser_tmp_var || !name)
        return;

    while (curr)
    {
        t_pair *p = (t_pair *)curr->content;
        if (p && p->name
            && ft_strncmp(p->name, name, ft_strlen(name) + 1) == 0)
        {
            if (prev)
                prev->next = curr->next;
            else
                *parser_tmp_var = curr->next;

            free(p->name);
            free(p->value);
            free(p);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

/**
 * @brief Returns the value of a variable from the temporary variable list.
 *
 * Iterates through the list of temporary shell variables (t_temp_lst_exec)
 * and returns the value of the first node whose name matches `name`.
 *
 * @param temp_vars Pointer to the head of the temporary variable list.
 * @param name Name of the variable to find.
 * @return Pointer to the value string if found, NULL otherwise.
 */
char *get_temp_var_value(t_temp_lst_exec *temp_vars, const char *name)
{
    t_temp_lst_exec *curr;

    if (!temp_vars || !name)
        return NULL;

    curr = temp_vars;
    while (curr)
    {
        if (curr->name && ft_strncmp(curr->name, name, ft_strlen(name) + 1) == 0)
            return curr->value;
        curr = curr->next;
    }
    return NULL;
}

/**
 * @brief Returns the value of a variable from the parser's temporary variable list.
 *
 * Iterates through the list of parser variables (t_list containing t_pair)
 * and returns the value of the first node whose name matches `name`.
 *
 * @param parser_tmp_var Pointer to the head of the parser's temporary variable list.
 * @param name Name of the variable to find.
 * @return Pointer to the value string if found, NULL otherwise.
 */
char *get_parser_tmp_var_value(t_list *parser_tmp_var, const char *name)
{
    t_list *curr;

    if (!parser_tmp_var || !name)
        return NULL;

    curr = parser_tmp_var;
    while (curr)
    {
        t_pair *p = (t_pair *)curr->content;
        if (p && p->name && ft_strncmp(p->name, name, ft_strlen(name) + 1) == 0)
            return p->value;
        curr = curr->next;
    }
    return NULL;
}
