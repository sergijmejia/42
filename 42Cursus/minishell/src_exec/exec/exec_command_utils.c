/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:50:50 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:25:55 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "minishell_exec.h"
#include "env.h"
#include "utils.h"
#include "exec_search.h"
#include "exec_wildcard.h"

/**
 * @brief Configure and execute the child process in fork_and_exec().
 *
 * Restores default signal handlers and executes the command using
 * find_and_exec(). Exits the process with the returned status.
 *
 * @param node AST node containing the command and its arguments.
 * @param env_for_exec Environment array for the child process.
 */
static void	run_child_process(t_ast *node, char **env_for_exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	_exit(find_and_exec(node->value, env_for_exec));
}

/**
 * @brief Wait for a child process and update g_exit_status accordingly.
 *
 * @param pid Process ID of the child to wait for.
 */
static void	wait_child_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	else
		g_exit_status = 1;
}

/**
 * @brief Forks and executes a simple command.
 *
 * Handles child process creation, signal reset, and status update.
 * In the child process, executes the command found by find_and_exec().
 *
 * @param node AST node containing the command and its arguments.
 * @param env_for_exec Environment array for execution.
 * @note On failure sets g_exit_status = 1.
 */
void	fork_and_exec(t_ast *node, char **env_for_exec)
{
	pid_t	pid;

	if (!node || !env_for_exec || !node->value || !node->value[0])
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork failed");
		free_envp(env_for_exec);
		g_exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		run_child_process(node, env_for_exec);
		free_envp(env_for_exec);
		clean_ast(node);
	}
	wait_child_process(pid);
}

/**
 * @brief Check if a string is a valid export argument.
 *
 * Accepts:
 *  - VAR
 *  - VAR=value
 *
 * Rules:
 *  - First character: letter or '_'
 *  - Following characters before '=': letters, digits, or '_'
 *
 * @param arg Argument string to validate.
 * @return 1 if valid, 0 otherwise.
 */
int	check_export_args(const char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
