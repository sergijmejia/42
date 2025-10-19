/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:34:01 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/02 13:00:29 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que encuentra el primer parentesis*/
static int	find_right_parenthesis(t_list **token_list, int pos)
{
	t_list		*node;
	t_token_ast	*token;
	int			size;
	int			count;

	size = ft_lstsize(*token_list);
	count = 1;
	while (pos < size)
	{
		node = ft_lstpos(*token_list, pos);
		token = (t_token_ast *)(node->content);
		if (token->type == 9)
			count++;
		else if (token->type == 10)
			count--;
		if (count == 0)
			return (pos);
		pos++;
	}
	return (size);
}

/*Funcion que encuentra el nodo AND*/
int	find_specific(t_list **token_list, int type)
{
	t_token_ast	*token;
	int			pos;
	int			size;

	pos = 0;
	size = ft_lstsize(*token_list);
	while (pos < size)
	{
		token = (t_token_ast *)((ft_lstpos(*token_list, pos))->content);
		if ((int)(token->type) == type)
			return (pos);
		else if (token->type == 9)
		{
			pos = find_right_parenthesis(token_list, pos + 1);
			if (pos == size)
			{
				error_tr(token_list);
				return (size);
			}
		}
		else
			pos++;
	}
	return (-1);
}
