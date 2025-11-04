/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:13:02 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:33:52 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "exec_wildcard.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Expands a single argument if it contains a wildcard '*'.
 */
static void	expand_wildcard_arg(char *arg, char ***new_args, int *count)
{
	char	**matches;
	char	**tmp;
	int		j;

	matches = expand_wildcard(arg);
	j = 0;
	while (matches && matches[j])
	{
		tmp = safe_realloc(*new_args, sizeof(char *) * (*count + 2));
		if (!tmp)
		{
			free_split(*new_args);
			free_split(matches);
			perror("wildcard realloc failed");
			g_exit_status = 1;
			return ;
		}
		*new_args = tmp;
		(*new_args)[*count] = ft_strdup(matches[j]);
		(*new_args)[*count + 1] = NULL;
		(*count)++;
		j++;
	}
	free_split(matches);
}

/**
 * @brief Adds a non-wildcard argument to the new_args array.
 */
static int	add_normal_arg(char *arg, char ***new_args, int *count)
{
	char	**tmp;

	tmp = safe_realloc(*new_args, sizeof(char *) * (*count + 2));
	if (!tmp)
	{
		free_split(*new_args);
		perror("minishell: wildcard realloc failed");
		g_exit_status = 1;
		return (0);
	}
	*new_args = tmp;
	(*new_args)[*count] = ft_strdup(arg);
	(*new_args)[*count + 1] = NULL;
	(*count)++;
	return (1);
}

/**
 * @brief Expands all wildcard patterns in a command argument list.
 */
char	**expand_wildcards(char **args)
{
	char	**new_args;
	int		i;
	int		count;

	if (!args)
		return (NULL);
	new_args = NULL;
	count = 0;
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			expand_wildcard_arg(args[i], &new_args, &count);
		else if (!add_normal_arg(args[i], &new_args, &count))
			return (NULL);
		i++;
	}
	return (new_args);
}
