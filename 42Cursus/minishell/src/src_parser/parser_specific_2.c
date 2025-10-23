/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_specific_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:30:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 16:09:54 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que divide token list desde pos tomando el lado derecho*/
static t_list	**divide_back(t_list **token_list, int pos, int size)
{
	t_list		**new_list;
	t_list		*new_node;
	t_token_ast	*token;
	t_token_ast	*new_token;

	new_list = (t_list **) malloc (sizeof(t_list *));
	if (new_list == NULL)
		return (NULL);
	*new_list = NULL;
	while (pos < size)
	{
		token = (t_token_ast *)((ft_lstpos(*token_list, pos))->content);
		new_token = duplicate_token_tr(token);
		if (new_token == NULL)
			return (clean_tr(new_list));
		new_node = ft_lstnew(new_token);
		if (new_node == NULL)
		{
			delete_token_ast(new_token);
			return (clean_tr(new_list));
		}
		ft_lstadd_back(new_list, new_node);
		pos++;
	}
	return (new_list);
}

/*Funcion que gestiona la parte derecha de &&*/
t_ast	**back(t_list **token_list, int pos)
{
	t_list	**back_list;
	t_ast	**ast_right;
	int		size;

	size = ft_lstsize(*token_list);
	back_list = divide_back(token_list, pos + 1, size);
	if (back_list == NULL)
		return (NULL);
	ast_right = parser(back_list);
	clean_tr(back_list);
	return (ast_right);
}
