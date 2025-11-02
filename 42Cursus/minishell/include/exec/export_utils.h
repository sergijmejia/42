#ifndef EXPORT_UTILS_H
#define EXPORT_UTILS_H

#include "minishell_exec.h"

void insert_temp_var(t_temp_lst_exec **temp_vars, char *name, char *value);
int  count_vars(char **envp);
int  fill_all_vars(char **all_vars, char **envp);
void add_var(t_temp_lst_exec **temp_vars, char *arg,
              char ***envp, t_list **parser_tmp_vars);

#endif
