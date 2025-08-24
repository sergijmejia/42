/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_divider_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:39:46 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/22 20:00:57 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que selecciona el type en el nuevo token para simple*/
static t_token_type	select_single_type(char *str)
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
static t_token_type	select_double_type(char *str)
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

/*Funcion que agrega nodo de caracter especial simple*/
void	simple_special_char(t_list **token_list, int i)
{
	char	*str;
	int		len;
	t_list	*token;
	t_token	*new_token;
	t_list	*new;

	token = ft_lstpos(*token_list, i);
	if (!token)
		error_list(token_list);
	len = (int) ft_strlen(((t_token *)(token->content))->value);
	if (len == 1)
	{
		((t_token *)(token->content))->type = select_single_type(((t_token *)(token->content))->value);
		return ;
	}
	str = ft_substr(((t_token *)(token->content))->value, 1, len);
	if (!str)
		error_list(token_list);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
		error_token(token_list, str);
	new_token->value = str;
	new_token->type = TOKEN_WORD;
	str = ft_substr(((t_token *)(token->content))->value, 0, 1);
	if (!str)
	{
		delete_token(new_token);
		error_list(token_list);
	}
	new = ft_lstnew(new_token);
	if (!new)
		error_token_value(token_list, new_token, str);
	free(((t_token *)(token->content))->value);
	((t_token *)(token->content))->value = str;
	((t_token *)(token->content))->type = select_single_type(((t_token *)(token->content))->value);
	ft_lstadd_pos(token_list, new, i);
}

/*Funcion que agrega nodo de caracter especial doble*/
void	double_special_char(t_list **token_list, int i)
{
	char	*str;
	int		len;
	t_list	*token;
	t_token *new_token;
	t_list	*new;

	token = ft_lstpos(*token_list, i);
	if (!token)
		error_list(token_list);
	len = (int) ft_strlen(((t_token *)(token->content))->value);
	if (len == 2)
	{
		((t_token *)(token->content))->type = select_double_type(((t_token *)(token->content))->value);
		return ;
	}
	str = ft_substr(((t_token *)(token->content))->value, 2, len);
	if (!str)
		error_list(token_list);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
		error_token(token_list, str);
	new_token->value = str;
	new_token->type = TOKEN_WORD;
	str = ft_substr(((t_token *)(token->content))->value, 0, 2);
	if (!str)
	{
		delete_token(new_token);
		error_list(token_list);
	}
	new = ft_lstnew(new_token);
	if (!new)
		error_token_value(token_list, new_token, str);
	free(((t_token *)(token->content))->value);
	((t_token *)(token->content))->value = str;
	((t_token *)(token->content))->type = select_double_type(((t_token *)(token->content))->value);
	ft_lstadd_pos(token_list, new, i);
}
