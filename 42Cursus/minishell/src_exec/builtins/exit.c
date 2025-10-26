/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:41:14 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 00:33:36 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Exits the shell with an optional exit code.
 *
 * @param args Command arguments. args[1] may contain the exit code.
 * @return Never returns (exits the process)
 */
int	builtin_exit(char **args)
{
	int	code;

	if (!args || !args[1])
		code = g_exit_status;
	else
		code = ft_atoi(args[1]);
	exit(code);
}
