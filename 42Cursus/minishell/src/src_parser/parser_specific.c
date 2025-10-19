/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_specific.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:40:09 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/17 16:14:22 by smejia-a         ###   ########.fr       */
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
			return (error_tr(new_list));
		ft_lstadd_back(new_list, new_node);
		i++;
	}
	return (new_list);
}

/*Funcion que gestiona la parte izquierda de &&*/
static t_ast	**front(t_list **token_list, int pos)
{
	t_list	**front_list;
	t_ast	**ast_left;

	front_list = divide_front(token_list, pos);
	if (front_list == NULL)
		return (NULL);
	ast_left = parser(front_list);
	error_tr(front_list);
	return (ast_left);
}

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
			return (error_tr(new_list));
		new_node = ft_lstnew(new_token);
		if (new_node == NULL)
		{
			delete_token_ast(new_token);
			return (error_tr(new_list));
		}
		ft_lstadd_back(new_list, new_node);
		pos++;
	}
	return (new_list);
}

/*Funcion que gestiona la parte derecha de &&*/
static t_ast	**back(t_list **token_list, int pos)
{
	t_list	**back_list;
	t_ast	**ast_right;
	int		size;

	size = ft_lstsize(*token_list);
	back_list = divide_back(token_list, pos + 1, size);
	if (back_list == NULL)
		return (NULL);
	ast_right = parser(back_list);
	error_tr(back_list);
	return (ast_right);
}

/*Funcion que gestiona un nodo en pos*/
t_ast	**parser_specific(t_list **token_list, int pos)
{
	t_ast	**ast_list;
	t_ast	**ast_right;
	t_ast	**ast_left;

	ast_list = create_ast(token_list, pos);
	if (ast_list == NULL)
		return (NULL);
	ast_left = front(token_list, pos);
	if (ast_left == NULL)
		return (error_ast(ast_list));
	(*ast_list)->left_ast = *ast_left;
	free(ast_left);
	ast_right = back(token_list, pos);
	if (ast_right == NULL)
		return (error_ast(ast_list));
	(*ast_list)->right_ast = *ast_right;
	free(ast_right);
	return (ast_list);
}
