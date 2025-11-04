/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:02:37 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 18:02:57 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_LOGIC_H
# define EXEC_LOGIC_H

# include "minishell_exec.h"

void	exec_and(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);
void	exec_or(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);
void	exec_parenthesis(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);

#endif
