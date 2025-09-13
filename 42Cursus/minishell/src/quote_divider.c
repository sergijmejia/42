/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_divider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:10:04 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/03 14:08:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Tengo que modificar esta funcion para que tome los datos de un TOKEN_WORD y
 *e inserte el resultado en la lista ya existente*/

#include "minishell.h"

/*Funcion que indica la posicion de las siguientes comillas.
Retorna -1 en caso de no encontrar*/
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
				return (pos);
		}
		pos++;
	}
	return (-1);
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

/*Funcion que crea un nodo TOKEN_WORD*/
static t_list	*new_word(char *str)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
		return (NULL);
	new_token->type = TOKEN_WORD;
	new_token->value = str;
	new_node = ft_lstnew(new_token);
	if (!new_node)
		free(new_token);
	return (new_node);
}

/*Funcion que agrega a la lista el texto encontrado entre comillas*/
static t_list	*new_quote(char *str, int c)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
		return (NULL);
	if (c == '\'')
		new_token->type = TOKEN_STRING_LITERAL;
	else if (c == '\"')
		new_token->type = TOKEN_EXPANDIBLE_STRINGS;
	new_token->value = str;
	new_node = ft_lstnew(new_token);
	if (!new_node)
		free(new_token);
	return (new_node);
}

static t_list	**divide_word(t_list **token_list, int i, int pos, int len)
{
	char	*new_str;
	t_list	*node;
	t_list	*new_node;

	node = ft_lstpos(*token_list, i);
	new_str = ft_substr(((t_token *)(node->content))->value, 0, pos);
	if (!new_str)
		return (NULL);
	new_node = new_word(new_str);
	if (!new_node)
	{
		free(new_str);
		return (NULL);
	}
	new_str = ft_substr(((t_token *)(node->content))->value, pos, len);
	if (!new_str)
	{
		error_list(&new_node);
		return (NULL);
	}
	free(((t_token *)(node->content))->value);
	((t_token *)(node->content))->value = new_str;
	ft_lstadd_pos(token_list, new_node, i);
	return (token_list);
}

static t_list	**divide_quote(t_list **token_list, int i, int len)
{
	t_list	*node;
	int		len_quote;
	char	*new_str;
	char	*str;
	t_list	*new_node;

	node = ft_lstpos(*token_list, i);
	str = ((t_token *)(node->content))->value;
	len_quote = count_quote_char(str);
	new_str = ft_substr(str, 1, len_quote - 1);
	if (!new_str)
		return (NULL);
	new_node = new_quote(new_str, str[0]);
	if (!new_node)
		return (NULL);
	new_str = ft_substr(str, len_quote + 1, len);
	if (!new_str)
	{
		error_list(&new_node);
		return (NULL);
	}
	free(((t_token *)(node->content))->value);
	((t_token *)(node->content))->value = new_str;
	ft_lstadd_pos(token_list, new_node, i);
	return (token_list);
}

/*Funcion que maneja el caso en que se han localizado comillas*/
static t_list	**quotes_found(t_list **token_list, int	i, int pos)
{
	t_list	*node;
	int		len;
	char	*str;

	node = ft_lstpos(*token_list, i);
	if (!node)
		return (NULL);
	str = ((t_token *)(node->content))->value;
	len = (int) ft_strlen(str);
	if (pos > 0)
	{
		if (divide_word(token_list, i, pos, len) == NULL)
			return (NULL);
	}
	else
	{
		if (divide_quote(token_list, i, len) == NULL)
			return (NULL);
	}
	return (token_list);
}

/*Se busca si lleva comillas o no*/
t_list	**add_quote_nodes(t_list **token_list, int i)
{
	int		pos;
	char	*str;
	t_list	*node;

	node = ft_lstpos(*token_list, i);
	if (!node)
		return (NULL);
	str = ((t_token *)(node->content))->value;
	pos = pos_next_quote(str);
	if (pos == -1)
		return (token_list);
	else
	{
		if (quotes_found(token_list, i, pos) == NULL)
			return (NULL);
	}
	return (token_list);
}

/*Funcion que divide un texto de entrada por comillas*/
/*Se busca si lleva comillas o no. pos = 0 no hay, pos != 0 si hay*/
t_list	**quote_divider(t_list **token_list)
{
	/*t_token	*token;
	t_list	*new_node;
	char	*str;
	int		pos;*/
	t_token	*token;
	t_list	*node;
	int		len;
	int		i;

	len = ft_lstsize(*token_list);
	i = 0;
	while (i < len)
	{
		node = ft_lstpos(*token_list, i);
		if (!node)
			return (error_list(token_list));
		token = (t_token*)(node -> content);
		if (token->type == TOKEN_WORD)
		{
			if (add_quote_nodes(token_list, i) == NULL)
				return (error_list(token_list));
		}
		i++;
		len = ft_lstsize(*token_list);
	}
	return (token_list);
	/*pos = pos_next_quote(str);
	if (pos == 0)
	{
		token = (t_token *) malloc (sizeof (t_token));
		if (!token)
			return (error_list(token_list));
		token->value = ft_strdup(str);
		if (!(token->value))
			return (error_token(token_list, token));
		token->type = TOKEN_WORD;
		new_node = ft_lstnew(token);
		if (!new_node)
			return (error_token(token_list, token));
		ft_lstadd_back(token_list, new_node);
		return (token_list);
	}
	else if (pos > 0)
	{
		if (quotes_found(token_list, &str, pos) == NULL)
			return (NULL);
		if (quote_divider(token_list, str) == NULL)
			return (NULL);
	}
	return (token_list);*/
}
