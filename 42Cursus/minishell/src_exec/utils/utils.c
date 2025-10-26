/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:02:37 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 16:27:47 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param split Array of strings to free
 */
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief Finds the value of a variable in the temporary execution list.
 *
 * @param var The name of the variable to search for.
 * @param tmp_var Pointer to the head of the temporary variable list.
 * @return char* The value of the variable if found, or NULL if not found.
 */
char	*find_var_exec(char *var, t_temp_lst_exec *tmp_var)
{
	size_t			var_len;
	size_t			name_len;
	size_t			cmp_result;
	t_temp_lst_exec	*curr;

	curr = tmp_var;
	var_len = ft_strlen(var);
	while (curr)
	{
		name_len = ft_strlen(curr->name);
		cmp_result = ft_strncmp(curr->name, var, var_len);
		if (name_len == var_len && cmp_result == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
