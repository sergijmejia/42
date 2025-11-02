#ifndef AST_H
# define AST_H

# include "minishell_exec.h"

t_ast	*new_command(char **argv);
t_ast	*new_binary_op(t_type_parser type, t_ast *left, t_ast *right);
t_ast	*new_redirection(t_type_parser type, t_ast *cmd, char *filename);
t_ast	*new_assignment(char *assign_str);
void	free_ast(t_ast *node);

#endif

