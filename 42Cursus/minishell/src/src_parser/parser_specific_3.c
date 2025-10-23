/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_specific_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:34:18 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 16:10:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona el loop de divide_front*/
static t_list	*divide_front_loop(t_list **token_list, int i)
{
	t_token_ast	*token;
	t_token_ast	*new_token;
	t_list		*new_node;

	token = (t_token_ast *)((ft_lstpos(*token_list, i))->content);
	new_token = duplicate_token_tr(token);
	if (new_token == NULL)
		return (NULL);
	new_node = ft_lstnew(new_token);
	if (new_node == NULL)
	{
		delete_token_ast(new_token);
		return (NULL);
	}
	return (new_node);
}

/*Funcion que divide token list hasta pos tomando el lado izquierdo*/
static t_list	**divide_front(t_list **token_list, int pos)
{
	t_list		**new_list;
	t_list		*new_node;
	int			i;

	new_list = (t_list **) malloc (sizeof(t_list *));
	if (new_list == NULL)
		return (NULL);
	*new_list = NULL;
	i = 0;
	while (i < pos)
	{
		new_node = divide_front_loop(token_list, i);
		if (new_node == NULL)
			return (clean_tr(new_list));
		ft_lstadd_back(new_list, new_node);
		i++;
	}
	return (new_list);
}

/*Funcion que gestiona la parte izquierda de &&*/
t_ast	**front(t_list **token_list, int pos)
{
	t_list	**front_list;
	t_ast	**ast_left;

	front_list = divide_front(token_list, pos);
	if (front_list == NULL)
		return (NULL);
	ast_left = parser(front_list);
	clean_tr(front_list);
	return (ast_left);
}
