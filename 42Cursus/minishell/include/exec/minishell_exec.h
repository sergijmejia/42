/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 02:21:30 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 18:16:23 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include "minishell.h"
/*
extern int g_exit_status;

typedef enum e_type_parser
{
	TOKEN_P_COMMAND,
	TOKEN_P_PIPE,
	TOKEN_P_GT,
	TOKEN_P_DOUBLE_GT,
	TOKEN_P_LT,
	TOKEN_P_DOUBLE_LT,
	TOKEN_P_ASSIGNMENT,
	TOKEN_P_AND,
	TOKEN_P_OR,
	TOKEN_P_PARENTHESIS,
	TOKEN_P_NAME
}	t_type_parser;

typedef struct s_ast
{
	t_type_parser	type;
	char			**value;
	int				wildcard;
	struct s_ast	*left_ast;
	struct s_ast	*right_ast;
}	t_ast;
*/
typedef struct s_temp_lst_exec
{
	char					*name;
	char					*value;
	struct s_temp_lst_exec	*next;
}	t_temp_lst_exec;

#endif
