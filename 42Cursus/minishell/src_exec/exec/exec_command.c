/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:28:51 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 11:31:38 by rafaguti         ###   ########.fr       */
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
 * @brief Forks and executes the command.
 *
 * Handles errors, child execution and wait.
 *
 * @param node AST node with command and args.
 * @param env_for_exec Environment array for execve.
 */
static void	fork_and_exec(t_ast *node, char **env_for_exec)
{
	pid_t	pid;

	if (!env_for_exec)
		return ;
	pid = fork();
	if (pid == -1)
	{
		free_envp(env_for_exec);
		perror("minishell: fork failed");
		g_exit_status = 1;
		return ;
	}
	if (pid == 0)
		child_exec_command(node, env_for_exec);
	wait_child_and_update_status(pid);
}

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
void exec_command_aux(t_ast *node, t_temp_lst_exec **temp_vars,
                      char ***envp, char *last_arg)
{
    char **env_for_exec;

    update_env_var(envp, "_", last_arg);
    env_for_exec = build_envp(*temp_vars, *envp);
    if (!env_for_exec)
    {
        g_exit_status = 1;
        return;
    }
    fork_and_exec(node, env_for_exec);
}


/**
 * @brief Executes a simple command node (builtin or external).
 *
 * Handles wildcard expansion ('*') before execution.
 * If the command contains patterns like "*.c", these are expanded to
 * matching filenames in the current directory.
 *
 * Determines if the command is a builtin; executes builtins directly
 * in the parent process, or forks for external commands.
 *
 * @param node AST node containing the command and its arguments.
 * @param temp_vars Pointer to the temporary environment variable list.
 * @param envp Pointer to the original environment array.
 */
void	exec_command(t_ast *node, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var)
{
	char	*last_arg;

	if (!node || !node->value)
	{
		g_exit_status = 1;
		return ;
	}
	handle_wildcards(node);
	last_arg = get_last_arg(node->value);
	if (get_builtin_type(node->value[0]) != BUILTIN_UNKNOWN)
	{
		g_exit_status = exec_builtin(node, temp_vars, envp, parser_tmp_var);
		update_env_var(envp, "_", last_arg);
	}
	else
		exec_command_aux(node, temp_vars, envp, last_arg);
}
