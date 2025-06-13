/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:47:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/06/06 17:56:17 by smejia-a         ###   ########.fr       */
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
void	quote_divider(t_list **token_list, char *str);
void	space_divider(t_list **token_list);

/*Tipos de tokens almacenados en el parseo*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_STRING_LITERAL,
	TOKEN_EXPANDIBLE_STRINGS,
	TOKEN_PIPE,
	TOKEN_GT,
	TOKEN_DOUBLE_GT,
	TOKEN_LT,
	TOKEN_DOUBLE_LT
} t_token_type;

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
} t_token;

#endif
