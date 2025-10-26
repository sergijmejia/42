/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:00:50 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 02:26:17 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell_exec.h"

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param arr Array of strings to free
 */
static void	free_argv_copy(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Duplicates a NULL-terminated argument vector.
 *
 * Allocates a new array and duplicates each string. If allocation
 * fails at any point, the already allocated memory is freed.
 *
 * @param argv Argument vector to duplicate
 * @return A newly allocated copy of argv, or NULL on error
 */
char	**dup_argv(char **argv)
{
	int		count;
	int		i;
	char	**copy;

	if (!argv)
		return (NULL);
	count = 0;
	while (argv[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(argv[i]);
		if (!copy[i])
		{
			free_argv_copy(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}
