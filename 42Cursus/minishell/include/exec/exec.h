/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:59:33 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 18:00:51 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				fd_in;
	int				fd_out;
	char			*filename;
	t_temp_lst_exec	**temp_vars;
	char			***envp;
	t_list			**parser_tmp_var;
	int				valid;
}	t_exec_ctx;

// exec_redir.c
void	exec_redir(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);

// exec_redir_utils.c
int		open_redir_file(char *filename, int type);
char	*get_redir_filename_from_node(t_ast *node);
void	exec_redir_child(int fd_in, int fd_out, t_ast *node,
			t_exec_ctx *ctx);

// exec_redir_utils2.c
void	apply_redirection(int fd, int type);
void	exec_redir_run_child(int fd_in, int fd_out,
			t_ast *node, t_exec_ctx *ctx);
void	exec_redir_child(int fd_in, int fd_out, t_ast *node, t_exec_ctx *ctx);

// exec_ast.c
void	exec_ast(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);

// exec_ast_utils.c
int		has_command_in_assignment(t_ast *node);
void	update_env_with_assign(t_ast *assign, char ***env_for_exec);
void	exec_assignment_chain(t_ast *assign, t_exec_ctx *ctx,
			char ***env_for_exec);

// exec_command.c
void	exec_command(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);

// exec_pipe
void	exec_pipe(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);

// exec_heredoc.c
void	exec_heredoc(t_ast *node, t_temp_lst_exec **temp_vars,
			char ***envp, t_list **parser_tmp_var);

#endif
