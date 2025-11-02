#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell_exec.h"

typedef enum e_builtin
{
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_ECHO,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_EXIT,
	BUILTIN_ENV,
	BUILTIN_UNKNOWN,
	BUILTIN_HISTORY
}	t_builtin;

/* dispatcher */
int		exec_builtin(t_ast *node, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var);

/* helpers for each builtin */
int		builtin_cd(char **args, char ***envp);
int		builtin_pwd(char **envp);
int		builtin_echo(char **args, t_temp_lst_exec *tmp_var);
int		builtin_export(char **args, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_vars);
int 	builtin_history(void);
int		builtin_unset(char **args, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var);
int		builtin_exit(char **args, t_temp_lst_exec **temp_vars, char ***envp, t_list **parser_tmp_var);
int		builtin_env(char **envp);

/* utility */
t_builtin	get_builtin_type(char *name);

#endif
