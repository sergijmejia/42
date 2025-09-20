/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:47:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/20 12:07:21 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/libft/libft.h"
# include <aio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_status;

/*Funciones de testeo*/
void	print_lst(t_list *lst);
void	print_lst_tr(t_list *lst);

/*Lexer*/
t_list	**lexer(char *str);
int		check_parentheses_balance(char *str);
int		check_quote_balance (char *str);
t_list	**parentheses_divider(t_list **token_list, char *str);
t_list	**assignment_divider(t_list **token_list);
//t_list	**quote_divider(t_list **token_list);
t_list	**space_divider(t_list **token_list);
t_list	**special_char_divider(t_list **token_list);
t_list	**simple_special_char(t_list **token_list, int i);
t_list	**double_special_char(t_list **token_list, int i);
t_list	**find_command_option(t_list **token_list);
t_list	**find_wildcard(t_list **token_list);
t_list	**variable_expansion(t_list **token_list);
t_list	**delete_quotes(t_list **token_list);

/*Nueva funcion de listas -> a agregar a libft*/
void	ft_lstadd_pos(t_list **lst, t_list *new, int i);
void	ft_lstdel_pos(t_list **lst, void (*del)(void*), int x);
void	ft_lstdel_last(t_list **lst, void (*del)(void*));

/*Transicion Lexer/Parser*/
t_list	**assignment_selection(t_list **token_list);
t_list	**transition_lex_par(t_list **token_list);

/*Parser*/

/*Estructura de la lista de variables asignadas*/
typedef struct s_temp_lst
{
	char	*name;
	char	*value;
} t_temp_lst;

/*Estructuras Lexer*/
/*Tipos de tokens almacenados en el lexer*/
typedef enum e_type_lexer
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
	TOKEN_ASSIGNMENT_CANDIDATE,
	TOKEN_ASSIGNMENT_WORD,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_RPAREN,
	TOKEN_LPAREN,
	TOKEN_BACKGROUND,
	TOKEN_WILDCARD,
	TOKEN_REDIRECTION_WORD
} t_type_lexer;

/*Estructura token usada en el lexer*/
typedef struct s_token
{
	enum e_type_lexer	type;
	char				*value;
	int					finished;
} t_token;

/*Estructuas Parser*/
/*Tipos de tokens almacenados en el parser*/
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
	TOKEN_P_PARENTHESIS
} t_type_parser;

/*Estructura usada en el parser*/
typedef struct s_ast
{
	enum e_type_parser	type;
	char				**value;
	int					wildcard;
	struct s_ast		*left_ast;
	struct s_ast		*right_ast;
} t_ast;

/*Estructuras intermedias de transicion*/
/*Tipos de tokens en fase de transicion lexer/parser*/
typedef enum e_type_tr
{
	COMMAND,
	PIPE,
	GT,
	DOUBLE_GT,
	LT,
	DOUBLE_LT,
	ASSIGNMENT,
	AND,
	OR,
	L_PARENTHESIS,
	R_PARENTHESIS
} t_type_tr;

/*Estructura intermedia entre lexer y parser*/
typedef struct s_token_ast
{
	enum e_type_tr	type;
	char			**value;
	int				wildcard;
} t_token_ast;

/*Funnciones de limpieza*/
void	delete_token(void *content);
t_list  **error_token(t_list **token_list, t_token *token);
t_list  **error_list(t_list **token_list);
char	**free_str(char **str);
void	delete_token_ast(void *content);
t_list	**error_tr(t_list **token_list);

#endif
