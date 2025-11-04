/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:11:04 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 18:13:31 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_UTILS_H
# define EXPORT_UTILS_H

# include "minishell_exec.h"

// export_utils.c
int		is_valid_var_name(const char *name);
void	insert_temp_var(t_temp_lst_exec **temp_vars, char *name, char *value);
int		count_vars(char **envp);
int		fill_all_vars(char **all_vars, char **envp);
void	add_var(t_temp_lst_exec **temp_vars, char *arg,
			char ***envp, t_list **parser_tmp_vars);

// export_utils2.c
void	add_var(t_temp_lst_exec **temp_vars, char *arg,
			char ***envp, t_list **parser_tmp_vars);

#endif
