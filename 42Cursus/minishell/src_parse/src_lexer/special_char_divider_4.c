/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_divider_4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:00:17 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/28 11:18:01 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que selecciona el type en el nuevo token para simple*/
static t_type_lexer	select_single_type(char *str)
{
	if (*str == '>')
		return (TOKEN_GT);
	else if (*str == '<')
		return (TOKEN_LT);
	else if (*str == '|')
		return (TOKEN_PIPE);
	else if (*str == '&')
		return (TOKEN_BACKGROUND);
	else if (*str == ')')
		return (TOKEN_LPAREN);
	else if (*str == '(')
		return (TOKEN_RPAREN);
	else
		return (TOKEN_WORD);
}

/*Funcion que selecciona el type en el nuevo token para doble*/
static t_type_lexer	select_double_type(char *str)
{
	if (*str == '>')
		return (TOKEN_DOUBLE_GT);
	else if (*str == '<')
		return (TOKEN_DOUBLE_LT);
	else if (*str == '&')
		return (TOKEN_AND);
	else if (*str == '|')
		return (TOKEN_OR);
	else
		return (TOKEN_WORD);
}

/*Funcion que selecciona el type en el nuevo token*/
t_type_lexer	select_special_type(char *str, int n)
{
	t_type_lexer	type;

	if (n == 1)
		type = select_single_type(str);
	else
		type = select_double_type(str);
	return (type);
}
