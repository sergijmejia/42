/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:28:51 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:28:29 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "minishell_exec.h"
#include "env.h"
#include "utils.h"
#include "builtins.h"
#include "exec_search.h"
#include "exec_wildcard.h"
#include "exec_command_utils.h"

/**
 * @brief Expands wildcards ('*') in command arguments.
 *
 * Frees the original node->value and replaces it with the expanded result.
 *
 * @param node AST node containing the command arguments.
 */
void	handle_wildcards(t_ast *node)
{
	char	**expanded;

	expanded = expand_wildcards(node->value);
	if (expanded)
	{
		free_split(node->value);
		node->value = expanded;
	}
}

/**
 * @brief Returns the last argument of a command.
 *
 * @param args Command arguments array.
 * @return Pointer to the last argument, or the first if only one.
 */
char	*get_last_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
		return (args[i - 1]);
	return (args[0]);
}

/**
 * @brief Auxiliary function for exec_command().
 *
 * Updates '_' variable, prepares the environment and forks execution.
 *
 * @param node AST node with the command.
 * @param temp_vars Temporary variable list.
 * @param envp Environment pointer.
 * @param last_arg Last argument to set in environment variable '_'.
 */
void	exec_command_aux(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, char *last_arg)
{
	char	**env_for_exec;

	update_env_var(envp, "_", last_arg);
	env_for_exec = build_envp(*temp_vars, *envp);
	if (!env_for_exec)
	{
		g_exit_status = 1;
		return ;
	}
	fork_and_exec(node, env_for_exec);
	free_envp(env_for_exec);
}

/**
 * @brief Validate arguments for the 'export' builtin.
 *
 * Checks that all provided arguments to the 'export' command
 * are valid identifiers. Prints an error message and sets
 * g_exit_status = 1 if any argument is invalid.
 *
 * @param args Array of argument strings (full command, including "export").
 * @param i Starting index for argument validation (usually 1).
 * @return 1 if all arguments are valid, 0 otherwise.
 */
static int	validate_export_args(char **args, int i)
{
	while (args[i])
	{
		if (!check_export_args(args[i]))
		{
			ft_putendl_fd("minishell: export: not a valid identifier", 2);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Execute a simple command node (builtin or external).
 *
 * Handles wildcard expansion ('*'), determines if the command
 * is a builtin or external, and executes it accordingly.
 *
 * @param node AST node containing the command and its arguments.
 * @param temp_vars Pointer to the temporary environment variable list.
 * @param envp Pointer to the original environment array.
 * @param parser_tmp_var Parser temporary variables list.
 */
void	exec_command(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	int		i;
	char	*last_arg;

	if (!node || !node->value)
		return ((void)(g_exit_status = 1));
	handle_wildcards(node);
	last_arg = get_last_arg(node->value);
	if (get_builtin_type(node->value[0]) != BUILTIN_UNKNOWN)
	{
		if (ft_strncmp(node->value[0], "export", ft_strlen("export") + 1) == 0)
		{
			i = 1;
			if (!validate_export_args(node->value, i))
				return ;
		}
		g_exit_status = exec_builtin(node, temp_vars, envp, parser_tmp_var);
		update_env_var(envp, "_", last_arg);
	}
	else
		exec_command_aux(node, temp_vars, envp, last_arg);
}
