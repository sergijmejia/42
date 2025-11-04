/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wildcard.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:08:54 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 18:09:24 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_WILDCARD_H
# define EXEC_WILDCARD_H

# include <dirent.h>   // opendir, readdir, closedir
# include <stdlib.h>   // malloc, free
# include <string.h>   // strstr, strcmp
# include "libft.h"    // para ft_split, ft_strdup, etc.

// exec_wildcard.c
char	**expand_wildcards(char **args);

// exec_wildcard_utils.c
void	*safe_realloc(void *ptr, size_t new_size);
int		match_pattern(const char *pattern, const char *filename);
char	**expand_wildcard_loop(DIR *dir, const char *pattern);
char	**expand_wildcard(const char *pattern);

#endif
