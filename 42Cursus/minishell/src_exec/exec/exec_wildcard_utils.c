/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wildcard_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:13:02 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 14:31:15 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Safe realloc that frees old memory on failure.
 */
void	*safe_realloc(void *ptr, size_t new_size)
{
	void	*tmp;

	tmp = realloc(ptr, new_size);
	if (!tmp)
	{
		free(ptr);
		return (NULL);
	}
	return (tmp);
}

/**
 * @brief Matches a filename against a simple wildcard pattern.
 */
int	match_pattern(const char *pattern, const char *filename)
{
	const char	*asterisk;
	size_t		pre_len;
	size_t		suf_len;
	size_t		file_len;

	if (!pattern || !filename)
		return (0);
	if (!ft_strchr(pattern, '*'))
		return (ft_strlen(pattern) == ft_strlen(filename)
			&& ft_strncmp(pattern, filename, ft_strlen(pattern)) == 0);
	if (pattern[0] == '*' && pattern[1] == '\0')
		return (1);
	asterisk = ft_strchr(pattern, '*');
	pre_len = asterisk - pattern;
	suf_len = ft_strlen(asterisk + 1);
	file_len = ft_strlen(filename);
	if (file_len < pre_len + suf_len)
		return (0);
	if (pre_len && ft_strncmp(pattern, filename, pre_len) != 0)
		return (0);
	if (suf_len && ft_strncmp(filename + file_len - suf_len,
			asterisk + 1, suf_len) != 0)
		return (0);
	return (1);
}

/**
 * @brief Loops through directory entries and collects matches.
 */
char	**expand_wildcard_loop(DIR *dir, const char *pattern)
{
	struct dirent	*entry;
	char			**matches;
	char			**tmp;
	int				count;

	matches = NULL;
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
		{
			tmp = safe_realloc(matches, sizeof(char *) * (count + 2));
			if (!tmp)
			{
				free_split(matches);
				return (NULL);
			}
			matches = tmp;
			matches[count++] = ft_strdup(entry->d_name);
			matches[count] = NULL;
		}
		entry = readdir(dir);
	}
	return (matches);
}

/**
 * @brief Expands a single wildcard pattern in the current directory.
 */
char	**expand_wildcard(const char *pattern)
{
	DIR		*dir;
	char	**matches;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	matches = expand_wildcard_loop(dir, pattern);
	closedir(dir);
	return (matches);
}
