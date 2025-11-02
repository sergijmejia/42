#ifndef UTILS_H
#define UTILS_H

#include "minishell_exec.h"
// utils.c
void free_split(char **split);
char *find_var_exec(char *var, t_temp_lst_exec *tmp_var);

// dup_argv.c
char	**dup_argv(char **argv);

// clean.h
void	free_tmp_var_exec(t_temp_lst_exec *lst);

#endif

