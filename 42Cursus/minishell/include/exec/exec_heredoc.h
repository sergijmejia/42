/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:10:00 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/22 11:10:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_HEREDOC_H
# define EXEC_HEREDOC_H

# include "minishell_exec.h"
# include "env.h"

/**
 * @brief Context structure to pass multiple parameters to fork_exec_heredoc().
 */
typedef struct s_heredoc_ctx
{
	t_temp_lst_exec **temp_vars;
	char ***envp;
	t_list **parser_tmp_var;
	int		hd[2];
}	t_heredoc_ctx;

int	exec_heredoc_prepare(t_ast *node);
void	exec_heredoc(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);
#endif
