/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:41:14 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 00:33:36 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "libft.h"
#include "utils.h"
#include "env.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Exits the shell, freeing all memory.
 *
 * @param args Command arguments. args[1] may contain exit code.
 * @param env Duplicated environment array.
 * @param tmp_var Executor temporary list.
 * @param parser_tmp_var Parser variable list.
 */
int		builtin_exit(char **args, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	int	code;

	if (!args || !args[1])
		code = g_exit_status;
	else
		code = ft_atoi(args[1]);
	printf("exit\n");
	if (temp_vars && *temp_vars)
		free_tmp_var_exec(*temp_vars);
	if (parser_tmp_var && *parser_tmp_var)
		ft_lstclear(parser_tmp_var, free_tmp_var_p);
	if (envp && *envp)
	{
		free_envp(*envp);
		*envp = NULL;
	}
	*temp_vars = NULL;
	*parser_tmp_var = NULL;
	*envp = NULL;
	exit(code);
}
