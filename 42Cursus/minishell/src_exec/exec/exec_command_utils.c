/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:50:50 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/22 10:50:51 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell_exec.h"
#include "env.h"
#include "utils.h"
#include "exec_search.h"
#include "exec_wildcard.h"

/**
 * @brief Executes the command in the child process.
 *
 * Restores default signals and calls find_and_exec.
 *
 * @param node AST node containing the command.
 * @param env_for_exec Environment array for execve.
 */
void	child_exec_command(t_ast *node, char **env_for_exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	_exit(find_and_exec(node->value, env_for_exec));
}

/**
 * @brief Waits for the child process and updates g_exit_status.
 *
 * @param pid PID of the forked child.
 */
void	wait_child_and_update_status(pid_t pid)
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
