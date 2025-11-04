/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:41:04 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:05:47 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_utils.h"
#include "builtins.h"
#include "libft.h"
#include "env.h"
#include "exec.h"
#include <stdlib.h>

/**
 * @brief Removes a variable from envp by name.
 *
 * Frees only the line corresponding to the variable.
 *
 * @param name Variable name
 * @param envp Pointer to environment array
 */
static void	unset_assignment_safe(const char *name, char ***envp)
{
	int		i;
	int		j;
	size_t	len;

	if (!name || !envp || !*envp)
		return ;
	len = ft_strlen(name);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) == 0
			&& (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			j = i;
			while ((*envp)[j + 1])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			(*envp)[j] = NULL;
			break ;
		}
		i++;
	}
}

/**
 * @brief Builtin unset: removes variables from local and environment.
 *
 * @param args Array of command arguments (args[1..] are variable names)
 * @param temp_vars Pointer to shell temporary variables list
 * @param envp Pointer to shell environment array
 * @param parser_tmp_var Parser's temporary variables table
 * @return Exit status (0 on success)
 */
int	builtin_unset(char **args, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	int	i;

	if (!args || !args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (envp && *envp)
			unset_assignment_safe(args[i], envp);
		remove_local_var(temp_vars, args[i]);
		remove_parser_tmp_var(parser_tmp_var, args[i]);
		i++;
	}
	return (0);
}
