#ifndef EXEC_COMMAND_UTILS_H
# define EXEC_COMMAND_UTILS_H

# include "minishell_exec.h"

void	child_exec_command(t_ast *node, char **env_for_exec);
void	wait_child_and_update_status(pid_t pid);

#endif
