/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:40:42 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 10:24:33 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * @brief Prints the current working directory like Bash
 * Uses the logical PWD from envp if valid, otherwise getcwd().
 */
int	builtin_pwd(char **envp)
{
	char	*pwd;
	char	cwd[1024];

	pwd = get_env_val(envp, "PWD");
	if (pwd && *pwd)
	{
		ft_putendl_fd(pwd, 1);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}
