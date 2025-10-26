/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:41:04 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/25 11:00:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_utils.h"
#include "builtins.h"
#include "libft.h"
#include "env.h"
#include "exec.h"
#include <stdlib.h>


/**
 * @brief Builtin unset: removes variables from local and environment.
 *
 * Bash-like behavior:
 *  - Removes all occurrences of a variable from the shell's local variables.
 *  - Removes the variable from the global environment (envp) if it exists.
 *
 * This function handles multiple variables passed as arguments:
 * unset VAR1 VAR2 ...
 *
 * @param args Array of command arguments (args[1..] are variable names)
 * @param temp_vars Pointer to the list of temporary shell variables
 * @param envp Pointer to the shell's global environment array
 * @return Exit status: 0 on success, 1 if args or temp_vars is NULL
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
			unset_assignment(args[i], envp);
		remove_local_var(temp_vars, args[i]);
        remove_parser_tmp_var(parser_tmp_var, args[i]);

		i++;
	}
	return (0);
}
