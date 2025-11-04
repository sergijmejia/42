/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:54:49 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 17:54:57 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell_exec.h"

t_ast	*new_command(char **argv);
t_ast	*new_binary_op(t_type_parser type, t_ast *left, t_ast *right);
t_ast	*new_redirection(t_type_parser type, t_ast *cmd, char *filename);
t_ast	*new_assignment(char *assign_str);
void	free_ast(t_ast *node);

#endif
