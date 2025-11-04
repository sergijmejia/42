/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:07:02 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 11:54:38 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cd.c
 * @brief Bash-perfect 'cd' builtin implementation for minishell
 *
 * Features:
 *  - cd without arguments → goes to $HOME, prints error if HOME unset
 *  - cd - → switches to OLDPWD and prints it, error if OLDPWD unset
 *  - cd . or relative paths in deleted directories → prints Bash-style error
 *    and updates PWD logically (PWD=OLDPWD/.)
 *  - Correct updating of OLDPWD and PWD environment variables
 *  - Safe memory management: no crashes, no invalid free
 */

#include "env.h"
#include "builtins.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * @brief Determines the target directory for 'cd' and prints if necessary.
 *
 * Handles no-argument cd (HOME) and cd - (OLDPWD).
 *
 * @param args Command arguments
 * @param envp Environment array
 * @param print Flag to indicate if directory should be printed (for cd -)
 * @return Target directory string, or NULL if error (caller should handle)
 */
static char	*get_cd_target(char **args, char **envp, int *print)
{
	char	*target;

	*print = 0;
	if (!args[1])
	{
		target = get_env_val(envp, "HOME");
		if (!target)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
		return (ft_strdup(target));
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		target = get_env_val(envp, "OLDPWD");
		if (!target)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (NULL);
		}
		*print = 1;
		return (ft_strdup(target));
	}
	return (ft_strdup(args[1]));
}

/**
 * @brief Resolves the previous working directory before chdir.
 *
 * Uses getcwd if possible; falls back to PWD from env.
 *
 * @param pwd_before PWD before chdir
 * @return Newly allocated oldpwd string, or NULL on error
 */
static char	*resolve_oldpwd(char *pwd_before)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	else if (pwd_before)
		return (ft_strdup(pwd_before));
	else
		return (ft_strdup(""));
}

/**
 * @brief Performs the chdir to target and prints errors if it fails.
 *
 * @param target Target directory
 * @param oldpwd Previously resolved old working directory
 * @param print Flag to print target (for cd -)
 * @return 0 on success, 1 on failure
 */
static int	do_chdir(char *target, char *oldpwd, int print)
{
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(oldpwd);
		return (1);
	}
	if (print)
		ft_putendl_fd(target, 1);
	return (0);
}

/**
 * @brief Updates OLDPWD and PWD environment variables after chdir.
 *
 * Handles logical PWD if getcwd fails.
 *
 * @param envp Pointer to environment array
 * @param oldpwd Previous working directory
 * @param pwd_before PWD before chdir
 */
static void	update_cd_env(char ***envp, char *oldpwd, char *pwd_before)
{
	char	cwd[1024];
	char	*logical;

	update_env_var(envp, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(envp, "PWD", cwd);
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		if (pwd_before)
		{
			logical = ft_strjoin(pwd_before, "/.");
			if (logical)
			{
				update_env_var(envp, "PWD", logical);
				free(logical);
			}
		}
	}
}

/**
 * @brief Builtin 'cd' implementation.
 *
 * Supports: cd, cd -, relative paths, PWD/OLDPWD management.
 *
 * @param args Command arguments
 * @param envp Pointer to environment array
 * @return Exit status (0 on success)
 */
int	builtin_cd(char **args, char ***envp)
{
	char	*oldpwd;
	char	*pwd_before;
	char	*target;
	int		print;

	pwd_before = get_env_val(*envp, "PWD");
	target = get_cd_target(args, *envp, &print);
	if (!target)
		return (1);
	oldpwd = resolve_oldpwd(pwd_before);
	if (!oldpwd)
	{
		free(target);
		return (1);
	}
	if (do_chdir(target, oldpwd, print))
	{
		free(target);
		return (1);
	}
	update_cd_env(envp, oldpwd, pwd_before);
	free(oldpwd);
	free(target);
	return (0);
}
