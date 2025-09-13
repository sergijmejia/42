/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_divider_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:39:46 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/12 10:44:29 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que encuentra la siguiente comilla*/
static int	next_quote(char *str, int pos)
{
	char	c;

	c = str[pos];
	pos++;
	while (str[pos] && str[pos] != c)
		pos++;
	return (pos);
}

/*Verifica el type*/
static t_type_lexer	check_type(t_list *lst)
{
	char	*str;
	int		literal;
	int		i;

	literal = 0;
	i = 0;
	str = ((t_token *)(lst->content))->value;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i = next_quote(str, i);
			literal = 1;
		}
		if (str[i] == '\"')
			return (TOKEN_EXPANDIBLE_STRINGS);
		i++;
	}
	if (literal == 1)
		return (TOKEN_STRING_LITERAL);
	else
		return (TOKEN_WORD);
}

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

/*Funcion que agrega nodo de caracter especial simple*/
t_list	**simple_special_char(t_list **token_list, int i)
{
	char			*str;
	int				len;
	t_type_lexer	type;
	t_list			*token;
	t_token			*new_token;
	t_list			*new;

	token = ft_lstpos(*token_list, i);
	if (!token)
		return (NULL);
	len = (int) ft_strlen(((t_token *)(token->content))->value);
	if (len == 1)
	{
		type = select_single_type(((t_token *)(token->content))->value);
		((t_token *)(token->content))->type = type;
		return (token_list);
	}
	str = ft_substr(((t_token *)(token->content))->value, 1, len);
	if (!str)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free(str);
		return (NULL);
	}
	new_token->value = str;
	str = ft_substr(((t_token *)(token->content))->value, 0, 1);
	if (!str)
	{
		delete_token(new_token);
		return (NULL);
	}
	new = ft_lstnew(new_token);
	if (!new)
	{
		delete_token(new_token);
		free(str);
		return (NULL);
	}
	new_token->type = check_type(new);
	free(((t_token *)(token->content))->value);
	((t_token *)(token->content))->value = str;
	type = select_single_type(((t_token *)(token->content))->value);
	((t_token *)(token->content))->type = type;
	ft_lstadd_pos(token_list, new, i + 1);
	return (token_list);
}

/*Funcion que agrega nodo de caracter especial doble*/
t_list	**double_special_char(t_list **token_list, int i)
{
	char			*str;
	int				len;
	t_type_lexer	type;
	t_list			*token;
	t_token 		*new_token;
	t_list			*new;

	token = ft_lstpos(*token_list, i);
	if (!token)
		return (NULL);
	len = (int) ft_strlen(((t_token *)(token->content))->value);
	if (len == 2)
	{
		type = select_double_type(((t_token *)(token->content))->value);
		((t_token *)(token->content))->type = type;
		return (token_list);
	}
	str = ft_substr(((t_token *)(token->content))->value, 2, len);
	if (!str)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free(str);
		return (NULL);
	}
	new_token->value = str;
	str = ft_substr(((t_token *)(token->content))->value, 0, 2);
	if (!str)
	{
		delete_token(new_token);
		return (NULL);
	}
	new = ft_lstnew(new_token);
	if (!new)
	{
		delete_token(new_token);
		free(str);
		return (NULL);
	}
	new_token->type = check_type(new);
	free(((t_token *)(token->content))->value);
	((t_token *)(token->content))->value = str;
	type = select_double_type(((t_token *)(token->content))->value);
	((t_token *)(token->content))->type = type;
	ft_lstadd_pos(token_list, new, i + 1);
	return (token_list);
}
