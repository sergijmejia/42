#ifndef EXEC_WILDCARD_H
# define EXEC_WILDCARD_H

# include <dirent.h>   // opendir, readdir, closedir
# include <stdlib.h>   // malloc, free
# include <string.h>   // strstr, strcmp
# include "libft.h"    // para ft_split, ft_strdup, etc.

char	**expand_wildcards(char **args);

#endif

