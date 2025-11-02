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

void fork_and_exec(t_ast *node, char **env_for_exec)
{
    pid_t pid;
    int status;

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
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        _exit(find_and_exec(node->value, env_for_exec));
    }

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_exit_status = 128 + WTERMSIG(status);
    else
        g_exit_status = 1;
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
 * @param arg Argument string
 * @return 1 if valid, 0 if invalid
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