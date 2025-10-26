/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:49:50 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 16:07:59 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona el bucle de info_parenthesis*/
static t_list	*into_parenthesis_loop(t_list **token_list, int i)
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
static t_list	**into_parenthesis(t_list **token_list, int size)
{
	t_list		**new_list;
	t_list		*new_node;
	int			i;

	new_list = (t_list **) malloc (sizeof(t_list *));
	if (new_list == NULL)
		return (NULL);
	*new_list = NULL;
	i = 1;
	while (i < size - 1)
	{
		new_node = into_parenthesis_loop(token_list, i);
		if (new_node == NULL)
			return (error_tr(new_list));
		ft_lstadd_back(new_list, new_node);
		i++;
	}
	return (new_list);
}

/*Funcion que gestiona un nodo en pos*/
t_ast	**parser_parenthesis(t_list **token_list)
{
	t_ast	**ast_list;
	t_ast	**ast_par;
	t_list	**inside_list;
	int		size;

	ast_list = create_ast(token_list, 0);
	if (ast_list == NULL)
		return (NULL);
	size = ft_lstsize(*token_list);
	inside_list = into_parenthesis(token_list, size);
	if (inside_list == NULL)
		return (error_ast(ast_list));
	ast_par = parser(inside_list);
	clean_tr(inside_list);
	if (ast_par == NULL)
		return (error_ast(ast_list));
	(*ast_list)->left_ast = *ast_par;
	free(ast_par);
	return (ast_list);
}
