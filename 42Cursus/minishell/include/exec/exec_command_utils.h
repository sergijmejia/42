#ifndef EXEC_COMMAND_UTILS_H
# define EXEC_COMMAND_UTILS_H

# include "minishell_exec.h"

void    fork_and_exec(t_ast *node, char **env_for_exec);
int	check_export_args(const char *arg);

#endif