/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:29:22 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 11:21:17 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "minishell_exec.h"
#include "exec_path.h"
#include "exec_search.h"

/**
 * @brief Attempts to execute the command directly if it contains a '/'.
 *
 * @param argv Command arguments
 * @param envp Environment array
 * @return Exit code (127 if not found, -1 if no direct execution attempted)
 */
static int	try_direct_exec(char **argv, char **envp)
{
	int	i;

	if (!argv || !argv[0])
		return (127);
	i = 0;
	while (argv[0][i])
	{
		if (argv[0][i] == '/')
		{
			if (access(argv[0], X_OK) == 0)
				execve(argv[0], argv, envp);
			write(2, argv[0], ft_strlen(argv[0]));
			write(2, ": command not found\n", 20);
			return (127);
		}
		i++;
	}
	return (-1);
}

/**
 * @brief Tries to execute the command in each PATH directory.
 *
 * @param paths Array of PATH directories
 * @param argv Command arguments
 * @param envp Environment array
 * @return 127 if not found
 */
static int	split_path_and_try_exec(char **paths, char **argv, char **envp)
{
	char	*candidate;
	int		i;

	i = 0;
	while (paths[i])
	{
		candidate = join_path(paths[i], argv[0]);
		if (candidate && access(candidate, X_OK) == 0)
			execve(candidate, argv, envp);
		free(candidate);
		i++;
	}
	return (127);
}

/**
 * @brief Searches the command in PATH directories and executes it.
 *
 * @param argv Command arguments
 * @param envp Environment array
 * @return 127 if not found
 */
static int	search_in_path(char **argv, char **envp)
{
	char	*path_env;
	char	**paths;
	int		ret;

	path_env = get_path_from_env(envp);
	if (!path_env)
	{
		write(2, "minishell: ", 11);
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": No such file or directory\n", 28);
		return (127);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		return (127);
	ret = split_path_and_try_exec(paths, argv, envp);
	free_split(paths);
	write(2, "minishell: ", 11);
	write(2, argv[0], ft_strlen(argv[0]));
	write(2, ": command not found\n", 20);
	return (ret);
}

/**
 * @brief Wrapper that handles direct execution or PATH search.
 *
 * @param argv Command arguments
 * @param envp Environment array
 * @return Exit code
 */
int	find_and_exec(char **argv, char **envp)
{
	int	status;

	status = try_direct_exec(argv, envp);
	if (status != -1)
		return (g_exit_status = status);
	status = search_in_path(argv, envp);
	return (g_exit_status = status);
}
