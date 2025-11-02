#ifndef EXEC_H
# define EXEC_H

# include "minishell_exec.h"

typedef struct s_pair
{
	char	*name;
	char	*value;
}	t_pair;

// @brief Execution context structure for redirections.
typedef struct s_exec_ctx
{
	t_temp_lst_exec	**temp_vars;
	char			***envp;
	t_list			**parser_tmp_var;
}	t_exec_ctx;

void	exec_ast(t_ast *node, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var);
void	exec_command(t_ast *node, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var);
void	exec_pipe(t_ast *node, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var);
void	exec_redir(t_ast *node, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var);
void	exec_heredoc(t_ast *node, t_temp_lst_exec **temp_vars, char ***envp,  t_list **parser_tmp_var);

#endif
