#ifndef VAR_UTILS_H
#define VAR_UTILS_H

#include "minishell_exec.h" // para t_temp_lst_exec y t_list

void    remove_parser_tmp_var(t_list **parser_tmp_var, char *name);
void    remove_local_var(t_temp_lst_exec **temp_vars, const char *name);
char    *get_temp_var_value(t_temp_lst_exec *temp_vars, const char *name);
char    *get_parser_tmp_var_value(t_list *parser_tmp_var, const char *name);

#endif
