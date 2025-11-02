/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_divider_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:39:46 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/28 11:00:10 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	type = select_special_type(((t_token *)(token->content))->value, n);
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
	str = ft_substr(((t_token *)(token->content))->value, 0, n);
	if (!str)
		return (NULL);
	free(((t_token *)(token->content))->value);
	((t_token *)(token->content))->value = str;
	type = select_special_type(((t_token *)(token->content))->value, n);
	((t_token *)(token->content))->type = type;
	ft_lstadd_pos(token_list, new, i + 1);
	return (token_list);
}
