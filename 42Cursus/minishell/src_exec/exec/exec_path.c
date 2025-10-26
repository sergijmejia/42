/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:35:09 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 00:36:08 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "exec_path.h"

/**
 * @brief Creates a new string combining directory and command.
 *
 * Allocates memory for "dir/cmd". Caller must free the result.
 *
 * @param dir Directory path (e.g. "/usr/bin")
 * @param cmd Command name (e.g. "ls")
 * @return Newly allocated string or NULL on failure
 */
char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*res;

	if (!dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

/**
 * @brief Retrieves the PATH value from the environment array.
 *
 * @param envp Environment array
 * @return Pointer to the PATH value (after "PATH=") or NULL
 */
char	*get_path_from_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
