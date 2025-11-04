/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:40:48 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/03 18:55:32 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>

/**
 * @brief Checks if a given argument is a valid -n flag.
 *
 * Accepts multiple forms like `-n`, `-nn`, `-nnnn`, etc.
 *
 * @param arg The argument string to check
 * @return 1 if it's a valid -n flag, 0 otherwise
 */
static int	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Prints a single argument.
 *
 * Handles the special cases:
 * - "$$" → prints the shell's PID.
 * - "$?" → prints the last command's exit status.
 *
 * @param arg Argument string to print
 */
static void	print_single_arg(char *arg)
{
	char	*pid_str;
	char	*exit_str;

	if (!arg)
		return ;
	if (ft_strncmp(arg, "$$", 2) == 0 && arg[2] == '\0')
	{
		pid_str = ft_itoa(getpid());
		if (pid_str)
		{
			ft_putstr_fd(pid_str, 1);
			free(pid_str);
		}
	}
	else if (ft_strncmp(arg, "$?", 2) == 0 && arg[2] == '\0')
	{
		exit_str = ft_itoa(g_exit_status);
		if (exit_str)
		{
			ft_putstr_fd(exit_str, 1);
			free(exit_str);
		}
	}
	else
		ft_putstr_fd(arg, 1);
}

/**
 * @brief Executes the builtin `echo` command.
 *
 * Mimics Bash behavior:
 * - Handles one or more "-n" flags (e.g., `echo -n -n hello`).
 * - Prints "$$" as the shell's PID.
 * - Prints arguments separated by spaces.
 *
 * @param args Array of arguments, where args[0] is "echo"
 * @param tmp_var Temporary variable list (currently unused)
 * @return Always returns 0 (success)
 */
int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		print_single_arg(args[i]);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
