/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_divider.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:58:35 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/13 12:47:12 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que encuentra el primer parentesis*/
static int	find_next_parenthesis(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			return (i);
		i++;
	}
	return (-1);
}

/*Funcion que encuentra la posicion del parentesis que cierra open*/
static int	find_close_parenthesis(char *str, int open)
{
	int	count;
	i = 0;

	i = open;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(')
			count++;
		if (str[i] == ')')
			count--;
		if (count == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*Funcion cre crea un unico nodo en caso de no encontrar parentesis*/
static t_list	**create_unique_node(t_list **token_list, char *str, int len)
{
	char	*str_token;
	t_token	*new_token;
	t_list	*new_node;

	str_token = ft_strdup(str);
	if (!str_token)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free(str_token);
		return (NULL);
	}
	new_token->value = str_token;
	new_token->type = TOKEN_WORD;
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		delete_token(new_token);
		return (NULL);
	}
	ft_lstadd_back(token_list, new_node);
	return (token_list);
}

/*Funcion que gestiona la creacion del TOKEN_WORD hasta el parentesis*/
static t_list	**start_list(t_list **token_list, char *str, int open)
{
	char	*str_token;
	t_token	*new_token;
	t_list	*new_node;

	str_token = (char *) malloc (sizeof(char) * (open + 2));
	if (!str_token)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free(str_token);
		return (NULL);
	}
	ft_strlcpy(str_token, str, open + 2);
	new_token->value = str_token;
	new_token->type = TOKEN_WORD;
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		delete_token(new_token);
		return (NULL);
	}
	ft_lstadd_back(token_list, new_node);
	return (token_list);
}

/*Funcion que gestiona la creacion de la lista del contenido entre parentesis*/
static t_list	**parentheses_list(t_list **token_list, char *str, int open)
{
	int		close;
	char	*str_token;
	t_list	**new_token_list;

	close = find_close_parenthesis(str, open);
	str_token = (char *) malloc (sizeof(char) * (close - open));
	if (!str_token)
		return (NULL);
	ft_strlcpy(str_token, &str[open + 1], close - open);
	new_token_list = lexer(str_token);
	if (!new_token_list)
	{
		free(str_token);
		return (NULL);
	}
	ft_lstadd_back(token_list, *new_token_list);
	return (token_list);
}

/*Funcion que gestiona la creacion del TOKEN_WORD despues del parentesis*/
static t_list	**end_list(t_list **token_list, char *str, int close, int len)
{
	char	*str_token;
	t_token	*new_token;
	t_list	*new_node;

	str_token = (char *) malloc (sizeof(char) * (len - close + 1));
	if (!str_token)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free(str_token);
		return (NULL);
	}
	ft_strlcpy(str_token, &str[close], len - close + 1);
	new_token->value = str_token;
	new_token->type = TOKEN_WORD;
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		delete_token(new_token);
		return (NULL);
	}
	ft_lstadd_back(token_list, new_node);
	return (token_list);
}

/*Funcion que llama a lexer de forma recursiva para manejar los parentesis*/
t_list	**parentheses_divider(t_list **token_list, char *str)
{
	int		open;
	int		close;
	int		len;

	open = find_next_parenthesis(str);
	len = (int) ft_strlen(str);
	if (open == -1)
	{
		create_unique_node(token_list, str, len);
		return (token_list);
	}
	close = find_close_parenthesis(str, open);
	if (close == -1)
		return (error_list(token_list));
	if (start_list(token_list, str, open) == NULL)
		return (error_list(token_list));
	if (parentheses_list(token_list, str, open))
		return (error_list(token_list));
	if (end_list(token_list, str, close, len))
		return (error_list(token_list));
	return (token_list);
}
