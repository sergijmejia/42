/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:13:02 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/22 00:52:24 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Matches a filename against a simple wildcard pattern.
 *
 * Supports only one wildcard character '*', which can appear
 * anywhere in the pattern (no recursive or directory matching).
 *
 * Examples:
 * - "a*" matches "abc"
 * - "*c" matches "abc"
 * - "a*c" matches "abc"
 * - "*" matches any filename
 *
 * @param pattern  The wildcard pattern to match against.
 * @param filename The filename to test.
 * @return 1 if the filename matches the pattern, 0 otherwise.
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
 *
 * @param dir Opened DIR pointer.
 * @param pattern Wildcard pattern to match.
 * @return Dynamically allocated NULL-terminated array of matches.
 *         NULL on allocation failure or no matches.
 */
static char	**expand_wildcard_loop(DIR *dir, const char *pattern)
{
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = NULL;
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
		{
			matches = realloc(matches, sizeof(char *) * (count + 2));
			if (!matches)
			{
				closedir(dir);
				return (NULL);
			}
			matches[count++] = ft_strdup(entry->d_name);
			matches[count] = NULL;
		}
		entry = readdir(dir);
	}
	return (matches);
}

/**
 * @brief Expands a single wildcard pattern in the current directory.
 *
 * Opens the directory and scans entries via expand_wildcard_loop()
 *
 * @param pattern Wildcard pattern to expand.
 * @return NULL-terminated array of matching filenames or NULL if none/failed.
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

/**
 * @brief Expands a single argument if it contains a wildcard '*'.
 *
 * Allocates space in new_args and appends the expanded matches
 * from the current directory. Updates count.
 *
 * @param arg The argument string to expand.
 * @param new_args Pointer to the current array of expanded arguments.
 * @param count Pointer to the number of arguments currently in new_args.
 */
static void	expand_wildcard_arg(char *arg, char ***new_args, int *count)
{
	char	**matches;
	int		j;

	matches = expand_wildcard(arg);
	j = 0;
	while (matches && matches[j])
	{
		*new_args = realloc(*new_args, sizeof(char *) * (*count + 2));
		(*new_args)[*count] = ft_strdup(matches[j]);
		(*new_args)[*count + 1] = NULL;
		(*count)++;
		j++;
	}
	if (matches)
		free_split(matches);
}

/**
 * @brief Expands all wildcard patterns in a command argument list.
 *
 * Iterates through each argument in the array and replaces any argument
 * containing '*' with the matching filenames in the current directory.
 * Example:
 *
 * echo *.c main.*
 *
 * Might expand to: *
 * echo exec_ast.c exec_command.c main.c main.h
 *
 * If no matches are found for a given pattern, the original argument
 * is left unchanged, just like in bash.
 *
 * @param args NULL-terminated array of command arguments.
 * @return A new NULL-terminated array with expanded arguments.
 *         The caller must free it with free_split().
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
			new_args = realloc(new_args, sizeof(char *) * (count + 2));
			new_args[count] = ft_strdup(args[i]);
			new_args[count + 1] = NULL;
			count++;
		}
		i++;
	}
	return (new_args);
}
