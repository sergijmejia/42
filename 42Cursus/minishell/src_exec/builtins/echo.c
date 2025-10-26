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
 * @brief Determines if the newline should be printed based on first argument.
 *
 * @param arg First argument
 * @return 1 if newline should be printed, 0 if suppressed
 */
static int	check_newline(char *arg)
{
    int	i;

    if (!arg)
        return (1);
    if (arg[0] != '-')
        return (1);
    i = 1;
    if (arg[i] == '\0')
        return (1);
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

/**
 * @brief Prints a single argument, expanding it if it starts with '$'.
 *
 * @param arg Argument string
 * @param tmp_var Temporary variable list
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
 * @brief Executes the builtin 'echo'.
 *
 * Handles the -n flag and variable expansion.
 *
 * @param args Array of arguments
 * @param tmp_var Temporary variable list
 * @return Exit status (always 0)
 */
int	builtin_echo(char **args, t_temp_lst_exec *tmp_var)
{
    int	i;
    int	newline;

    i = 1;
    newline = check_newline(args[i]);
    if (args[i] && newline == 0)
        i++;
    while (args && args[i])
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
