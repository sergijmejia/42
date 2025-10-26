/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:12:48 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/21 12:40:55 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

/**
 * @brief Maps string command to builtin type
 *
 * @param name Command name
 * @return t_builtin enum value
 */
t_builtin	get_builtin_type(char *name)
{
	if (!name)
		return (BUILTIN_UNKNOWN);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (BUILTIN_CD);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (BUILTIN_PWD);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (BUILTIN_ECHO);
	if (ft_strncmp(name, "export", 7) == 0)
		return (BUILTIN_EXPORT);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (BUILTIN_UNSET);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (BUILTIN_EXIT);
	if (ft_strncmp(name, "env", 4) == 0)
		return (BUILTIN_ENV);
	if (ft_strncmp(name, "history", 8) == 0)
		return (BUILTIN_HISTORY);
	return (BUILTIN_UNKNOWN);
}

/**
 * @brief Executes a builtin command by dispatching to the correct function.
 *
 * @param node AST node containing the command and arguments
 * @param temp_vars Temporary environment variable list
 * @param envp Environment array
 * @return Exit status
 */
int	exec_builtin(t_ast *node, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var)
{
	t_builtin	type;

	if (!node || !node->value || !node->value[0])
		return (1);
	type = get_builtin_type(node->value[0]);
	if (type == BUILTIN_PWD)
		return (builtin_pwd(*envp));
	else if (type == BUILTIN_ECHO)
		return (builtin_echo(node->value, *temp_vars));
	else if (type == BUILTIN_CD)
		return (builtin_cd(node->value, envp));
	else if (type == BUILTIN_EXIT)
		return (builtin_exit(node->value));
	else if (type == BUILTIN_ENV)
		return (builtin_env(*envp));
	else if (type == BUILTIN_EXPORT)
		return (builtin_export(node->value, temp_vars, envp, parser_tmp_var));
	else if (type == BUILTIN_UNSET)
		return (builtin_unset(node->value, temp_vars, envp, parser_tmp_var));
	else if (type == BUILTIN_HISTORY)
		return (builtin_history());
	return (1);
}
