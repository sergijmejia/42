/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_divider_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:34:30 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 15:48:13 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que encuentra el primer parentesis*/
int	find_next_parenthesis(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = next_quote(str, i);
		if (str[i] == '(')
			return (i);
		i++;
	}
	return (-1);
}

/*Funcion que encuentra la posicion del parentesis que cierra open*/
int	close_parenthesis(char *str, int open)
{
	int	count;

	count = 0;
	while (str[open])
	{
		if (str[open] == '\'' || str[open] == '\"')
			open = next_quote(str, open);
		if (str[open] == '(')
			count++;
		if (str[open] == ')')
			count--;
		if (count == 0)
			return (open);
		open++;
	}
	return (-1);
}

/*Funcion que crea un unico nodo en caso de no encontrar parentesis*/
t_list	**create_unique_node(t_list **token_list, char *str)
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
	new_token->finished = 0;
	new_token->quote = 0;
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		delete_token(new_token);
		return (NULL);
	}
	ft_lstadd_back(token_list, new_node);
	return (token_list);
}
