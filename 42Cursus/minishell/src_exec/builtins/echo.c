/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:40:48 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 10:50:43 by rafaguti         ###   ########.fr       */
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
 * @brief Prints a single argument, expanding it if it starts with '$'.
 *
 * @param arg Argument string to print
 * @param tmp_var Temporary variable list for variable expansion
 */
static void	print_single_arg(char *arg, t_temp_lst_exec *tmp_var)
{
	char	*expanded;

	if (!arg)
		return ;
	if (arg[0] == '$')
	{
		expanded = find_var_exec(arg + 1, tmp_var);
		if (expanded)
			ft_putstr_fd(expanded, 1);
	}
	else
		ft_putstr_fd(arg, 1);
}

/**
 * @brief Executes the builtin `echo` command.
 *
 * Mimics Bash behavior:
 * - Handles one or more `-n` flags (e.g. `echo -n -n hello`).
 * - Expands variables beginning with `$`.
 * - Prints arguments separated by spaces.
 *
 * @param args Array of arguments (`args[0]` is "echo")
 * @param tmp_var Temporary variable list
 * @return Always returns 0 (success)
 */
int	builtin_echo(char **args, t_temp_lst_exec *tmp_var)
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
		print_single_arg(args[i], tmp_var);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
