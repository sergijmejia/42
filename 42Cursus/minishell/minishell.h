/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:47:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/07 17:58:15 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <aio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

/*Funciones de testeo*/
void	print_lst(t_list *lst);

/*Parse*/
t_list	*lexer(char *str);
int		check_parentheses_balance(char *str);
void	quote_divider(t_list **token_list, char *str);
void	space_divider(t_list **token_list);
void	special_char_divider(t_list **token_list);
void	simple_special_char(t_list **token_list, int i);
void	double_special_char(t_list **token_list, int i);
void	find_command_option(t_list **token_list);

/*Nueva funcion de listas -> a agregar a libft*/
void	ft_lstadd_pos(t_list **lst, t_list *new, int i);

/*Tipos de tokens almacenados en el parseo*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_COMMAND_OPTION,
	TOKEN_STRING_LITERAL,
	TOKEN_EXPANDIBLE_STRINGS,
	TOKEN_PIPE,
	TOKEN_GT,
	TOKEN_DOUBLE_GT,
	TOKEN_LT,
	TOKEN_DOUBLE_LT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_RPAREN,
	TOKEN_LPAREN,
	TOKEN_BACKGROUND,
	TOKEN_WILDCARD,
	TOKEN_EXPANDED_STRING
} t_token_type;

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	int					level;
} t_token;

#endif
