/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_union_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:02:23 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 13:06:55 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que junta los str de new y de token*/
static char	**str_nodes(t_token_ast *n, t_token_ast *t, int len_n, int len_t)
{
	char	**str;
	int		i;

	str = (char **) malloc ((len_n + len_t + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len_n)
	{
		str[i] = ft_strdup((n->value)[i]);
		if (str[i] == NULL)
			return (free_str(str));
		i++;
	}
	i = 0;
	while (i < len_t)
	{
		str[i + len_n] = ft_strdup((t->value)[i]);
		if (str[i + len_n] == NULL)
			return (free_str(str));
		i++;
	}
	str[len_n + len_t] = NULL;
	return (str);
}

/*Funcion que agrega el str del token en pos a new_token*/
/*Si el str de token es vacio lo descarta*/
static t_token_ast	**join_nodes(t_token_ast **new, t_token_ast *token)
{
	int		len_new;
	int		len_token;
	char	**str;

	if (*new == NULL)
	{
		*new = duplicate_token_tr(token);
		return (new);
	}
	len_new = calculate_strlen(*new);
	len_token = calculate_strlen(token);
	if ((len_token == 1) && (ft_strlen((token->value)[0]) == 0))
		return (new);
	if (len_new == -1 || len_token == -1)
		return (NULL);
	str = str_nodes(*new, token, len_new, len_token);
	if (str == NULL)
		return (NULL);
	free_str((*new)->value);
	(*new)->value = str;
	if (token->wildcard)
		(*new)->wildcard = 1;
	return (new);
}

/*Funcion que gestiona el loop de changed_token*/
static t_token_ast	**changed_token_loop(t_token_ast **new, t_token_ast *token)
{
	if (token->type == 0)
	{
		if (join_nodes(new, token) == NULL)
			return (NULL);
	}
	return (new);
}

/*Funcion que crea el nuevo nodo de union de todos los word*/
t_token_ast	*changed_token(t_list **token_list, int pos)
{
	t_token_ast	*token;
	t_token_ast	*new_token;
	t_list		*node;

	new_token = NULL;
	node = ft_lstpos(*token_list, pos);
	if (node == NULL)
		return (NULL);
	token = (t_token_ast *)(node->content);
	while (token->type != 1 && (token->type < 6 || token->type == 11))
	{
		if (changed_token_loop(&new_token, token) == NULL)
		{
			delete_token_ast(new_token);
			return (NULL);
		}
		pos++;
		node = ft_lstpos(*token_list, pos);
		if (node == NULL)
			break ;
		token = (t_token_ast *)(node->content);
	}
	return (new_token);
}
