/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:13:02 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/29 19:42:24 by rafaguti         ###   ########.fr       */
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
static void	*safe_realloc(void *ptr, size_t new_size)
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
static int	match_pattern(const char *pattern, const char *filename)
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
static char	**expand_wildcard_loop(DIR *dir, const char *pattern)
{
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = NULL;
	count = 0;
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
		{
			char **tmp = safe_realloc(matches, sizeof(char *) * (count + 2));
			if (!tmp)
			{
				free_split(matches);
				return (NULL);
			}
			matches = tmp;
			matches[count++] = ft_strdup(entry->d_name);
			matches[count] = NULL;
		}
	}
	return (matches);
}

/**
 * @brief Expands a single wildcard pattern in the current directory.
 */
static char	**expand_wildcard(const char *pattern)
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

/**
 * @brief Expands a single argument if it contains a wildcard '*'.
 */
static void	expand_wildcard_arg(char *arg, char ***new_args, int *count)
{
	char	**matches;
	int		j;

	matches = expand_wildcard(arg);
	j = 0;
	while (matches && matches[j])
	{
		char **tmp = safe_realloc(*new_args, sizeof(char *) * (*count + 2));
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
		else
		{
			char **tmp = safe_realloc(new_args, sizeof(char *) * (count + 2));
			if (!tmp)
			{
				free_split(new_args);
				perror("minishell: wildcard realloc failed");
				g_exit_status = 1;
				return (NULL);
			}
			new_args = tmp;
			new_args[count] = ft_strdup(args[i]);
			new_args[count + 1] = NULL;
			count++;
		}
		i++;
	}
	return (new_args);
}