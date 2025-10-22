/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:47:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 16:03:05 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <aio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_status;

/*Estructura de la lista de variables asignadas*/
typedef struct s_temp_lst
{
	char	*name;
	char	*value;
}	t_temp_lst;

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
	TOKEN_REDIRECTION_WORD,
    TOKEN_REDIRECTION_HEREDOC
}	t_type_lexer;

/*Estructura token usada en el lexer*/
typedef struct s_token
{
	enum e_type_lexer	type;
	char				*value;
	int					finished;
    int                 quote;
}	t_token;

/*Estructura auxiliar para poder manejar la cantidad de argumentos en la norma*/
typedef struct s_aux
{
	t_list	**token_list;
	t_list	**tmp_var;
	char	**env;
	int		x;
}	t_aux;

/*Estructuras de Transicion entre Lexer y Parser*/
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
	R_PARENTHESIS,
	NAME
}	t_type_tr;

/*Estructura intermedia entre lexer y parser*/
typedef struct s_token_ast
{
	enum e_type_tr	type;
	char			**value;
	int				wildcard;
    int             quote;
}	t_token_ast;

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
	TOKEN_P_PARENTHESIS,
	TOKEN_P_NAME
}	t_type_parser;

/*Estructura usada en el parser*/
typedef struct s_ast
{
	enum e_type_parser	type;
	char				**value;
	int					wildcard;
	struct s_ast		*left_ast;
	struct s_ast		*right_ast;
}	t_ast;

/*Funciones principales*/
char			**dup_env(char **envp);
int				check_env(char **envp);
t_list			**create_var_table(void);

/*Funciones de testeo*/
void			print_lst(t_list *lst);
void			print_lst_tr(t_list *lst);
void			print_ast(t_ast *ast_list);
void			print_str(char **str);

/*Utils*/
int				next_quote(char *str, int pos);
t_type_lexer	check_type(t_list *lst);
t_token_ast		*duplicate_token_tr(t_token_ast *token);
int				doublestr_len(char **str);
int				calculate_strlen(t_token_ast *token);
int				replace_string(char **str, char *new_str, int c_len, int pos);
char			*get_command(char *str, int x);

/*-----LEXER-----*/

t_list			**lexer(char *str, char **env, t_list **tmp_var);
int				check_parentheses_balance(char *str);
int				check_quote_balance(char *str);
t_list			**paren_divider(t_list **l, char *s, char **e, t_list **t);
int				find_next_parenthesis(char *str);
int				close_parenthesis(char *str, int open);
t_list			**create_unique_node(t_list **token_list, char *str);
t_list			**assignment_divider(t_list **token_list);
int				assignment_candidate(t_list **lst, int *i, int pos);
t_list			**generate_nodes(t_list **lst, int i, int start, int end);
t_list			*create_node(char *str, int start, int end, int type);
int				assignment_candidate(t_list **lst, int *i, int pos);
t_list			**space_divider(t_list **token_list);
t_list			**node_before_div(t_list **token_list, int i, int pos);
t_list			**special_char_divider(t_list **token_list);
t_list			**divide_special(t_list **token_list, int *i, char *sp_char);
t_list			**special_char(t_list **token_list, int i, int n);
t_list			**find_redirection(t_list **token_list);
t_list			**find_wildcard(t_list **token_list);
t_list			**var_expansion(t_list **lst, char **env, t_list **tmp_var);
t_list			**exp_string(t_list **lst, char **env, int x, t_list **tmp_var);
t_list			**delete_quotes(t_list **token_list);
char			*find_var(char *var, t_list **tmp_var);

/*Nueva funcion de listas -> a agregar a libft*/
void			ft_lstadd_pos(t_list **lst, t_list *new, int i);
void			ft_lstdel_pos(t_list **lst, void (*del)(void *), int x);
void			ft_lstdel_last(t_list **lst, void (*del)(void *));
char			*ft_getenv(char **env, const char *name);

/*-----TRANSICION LEXER/PARSER-----*/
t_list			**transition(t_list **lst, char **e, t_list **t, char **l);
t_list			**assignment_selection(t_list **token_list);
t_list			**transition_lex_par(t_list **token_list);
t_list			**command_union(t_list **token_list);
t_list			**syntax_and_heredoc(t_aux *aux, char **line);
int				heredoc(t_aux *aux, int pos, char **line);

/*-----PARSER-----*/

t_ast			**parser(t_list **token_list);
t_ast			**parser_specific(t_list **token_list, int pos);
t_ast			**parser_parenthesis(t_list **token_list);
t_ast			**create_ast(t_list **token_list, int pos);
int				find_specific(t_list **token_list, int type);

/*Funnciones de limpieza*/
void			delete_token(void *content);
t_list			**error_token(t_list **token_list, t_token *token);
t_list			**error_list(t_list **token_list);
char			**free_str(char **str);
void			delete_token_ast(void *content);
t_list			**error_tr(t_list **token_list);
void			delete_ast(void *content);
t_ast			**error_ast(t_ast **ast_list);
t_list			**error_syntax(t_list **token_list, int pos);
t_list			**clean_token(t_list **token_list, t_token *token);
t_list			**clean_list(t_list **token_list);

#endif
