/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_divider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:10:04 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/22 19:54:30 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que indica la posicion de las siguientes comillas.
Retorna 0 en caso de no encontrar*/
static int	pos_next_quote(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '\"')
		{
			if (str[pos] == str[pos + 1])
				pos++;
			else
				return (pos + 1);
		}
		pos++;
	}
	return (0);
}

/*Cuenta la cantidad de caracteres que hay dentro de las comillas*/
static int	count_quote_char(char *str)
{
	int		pos;
	char	c;

	pos = 1;
	if (str[0] == '\'')
		c = '\'';
	else if (str[0] == '\"')
		c = '\"';
	else
		return (-1);
	while (str[pos] != c)
	{
		if (!str[pos])
			return (-1);
		pos++;
	}
	return (pos);
}

/*Funcion que agrega a la lista el texto encontrado entre comillas*/
static void	new_quote(t_list **token_list, char **str)
{
	int		pos;
	t_token	*quote;
	char	*new_str;
	t_list	*new_node;

	quote = (t_token *) malloc (sizeof (t_token));
	if (!quote)
		error_token(token_list, *str);
	if (**str == '\'')
		quote->type = TOKEN_STRING_LITERAL;
	else if (**str == '\"')
		quote->type = TOKEN_EXPANDIBLE_STRINGS;
	pos = count_quote_char(*str);
	(*str)++;
	new_str = (char *) malloc (sizeof (char) * (pos));
	if (!new_str)
		error_token_value(token_list, quote, *str);
	new_str = (char *) ft_memmove(new_str, *str, pos - 1);
	new_str[pos - 1] = '\0';
	quote->value = new_str;
	new_node = ft_lstnew(quote);
	if (!new_node)
		error_token_value(token_list, quote, *str);
	ft_lstadd_back(token_list, new_node);
	*str = *str + pos;
	return ;
}

/*Funcion que maneja el caso en que se han localizado comillas*/
static void	quotes_found(t_list **token_list, char **str, int pos)
{
	t_list	*new_node;
	char	*new_str;
	t_token	*token;

	if (pos > 1)
	{
		token = (t_token *) malloc (sizeof (t_token));
		if (!token)
			error_token(token_list, *str);
		new_str = (char *) malloc (sizeof (char) * (pos));
		if (!new_str)
			error_token_value(token_list, token, *str);
		new_str = (char *) ft_memmove(new_str, *str, pos - 1);
		new_str[pos] = '\0';
		token->value = new_str;
		token->type = TOKEN_WORD;
		new_node = ft_lstnew(token);
		if (!new_node)
			error_token_value(token_list, token, *str);
		ft_lstadd_back(token_list, new_node);
	}
	*str = (*str) + pos - 1;
	new_quote(token_list, str);
}

/*Funcion que divide un texto de entrada por comillas*/
/*Se busca si lleva comillas o no. pos = 0 no hay, pos != 0 si hay*/
void	quote_divider(t_list **token_list, char *str)
{
	t_token	*token;
	t_list	*new_node;
	int		pos;

	pos = pos_next_quote(str);
	if (pos == 0)
	{
		token = (t_token *) malloc (sizeof (t_token));
		if (!token)
			error_token(token_list, str);
		token->value = ft_strdup(str);
		if (!(token->value))
			error_token_value(token_list, token, str);
		token->type = TOKEN_WORD;
		new_node = ft_lstnew(token);
		if (!new_node)
		{
			delete_token(token);
			error_token(token_list, str);
		}
		ft_lstadd_back(token_list, new_node);
		return ;
	}
	else if (pos > 0)
	{
		quotes_found(token_list, &str, pos);
		quote_divider(token_list, str);
	}
	return ;
}
