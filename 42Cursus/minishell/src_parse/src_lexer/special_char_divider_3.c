/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_divider_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:39:46 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/13 13:03:57 by smejia-a         ###   ########.fr       */
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

/*Funcion que selecciona el tupe en el nuevo token para doble*/
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

/*Funcion que genera el nuevo nodo con n caracteres*/
static t_list	*generate_new(t_list *token, int len, int n)
{
	t_list	*new;
	t_token	*new_token;
	char	*str;

	str = ft_substr(((t_token *)(token->content))->value, n, len);
	if (!str)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free(str);
		return (NULL);
	}
	new_token->value = str;
	new = ft_lstnew(new_token);
	if (!new)
	{
		delete_token(new_token);
		return (NULL);
	}
	new_token->type = check_type(new);
	new_token->finished = 0;
	return (new);
}

/*Funcion que asigna valores de un nodo con un string de n special*/
static t_list	**unique_special(t_list **token_list, int i, int n)
{
	t_list			*token;
	t_type_lexer	type;

	token = ft_lstpos(*token_list, i);
	if (!token)
		return (NULL);
	if (n == 1)
		type = select_single_type(((t_token *)(token->content))->value);
	else if (n == 2)
		type = select_double_type(((t_token *)(token->content))->value);
	else
		return (NULL);
	((t_token *)(token->content))->type = type;
	return (token_list);
}

/*Funcion que agrega nodo de caracter especial simple*/
t_list	**special_char(t_list **token_list, int i, int n)
{
	char			*str;
	int				len;
	t_type_lexer	type;
	t_list			*token;
	t_list			*new;

	token = ft_lstpos(*token_list, i);
	if (!token)
		return (NULL);
	len = (int) ft_strlen(((t_token *)(token->content))->value);
	if (len == n)
		return (unique_special(token_list, i, n));
	new = generate_new(token, len, n);
	if (new == NULL)
		return (NULL);
	str = ft_substr(((t_token *)(token->content))->value, 0, 1);
	if (!str)
		return (NULL);
	free(((t_token *)(token->content))->value);
	((t_token *)(token->content))->value = str;
	type = select_single_type(((t_token *)(token->content))->value);
	((t_token *)(token->content))->type = type;
	ft_lstadd_pos(token_list, new, i + 1);
	return (token_list);
}
