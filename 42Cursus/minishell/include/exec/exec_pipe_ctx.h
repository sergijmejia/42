/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_ctx.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:00:00 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 18:33:50 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPE_CTX_H
# define EXEC_PIPE_CTX_H

# include "minishell_exec.h"

typedef struct s_pipe_ctx
{
	t_temp_lst_exec	**temp_vars;
	char			***envp;
	t_list			**parser_tmp_var;
	int				fd[2];
}	t_pipe_ctx;
#endif
