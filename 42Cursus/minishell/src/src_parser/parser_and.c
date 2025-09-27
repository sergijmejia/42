/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:40:09 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/26 18:07:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que divide token list hasta pos tomando el lado izquierdo*/
static t_list	**divide_front(t_list **token_list, int pos) //---------> REVISAR
{
	t_list		**new_list;
	t_list		*new_node;
	t_token_ast	*token;
	t_token_ast	*new_token;
	int			i;

	new_list = (t_list	**) malloc (sizeof(t_list *));
	if (new_list == NULL)
		return (NULL);
	i = 0;
	while (i < 0)
	{
		token = (t_token_ast *)((ft_lstpos(*token_list, pos))->content);
		new_token = duplicate_token_tr(token);
		if (new_token == NULL)
			return (error_tr(new_list));
		new_node = ft_lstnew(new_token);
		if (new_node == NULL)
		{
			delete_token_ast(new_token);
			return (error_tr(new_lst));
		}
		ft_lstadd(*new_list, new_node);
		i++;
	}
	return (new_list);
}	

/*Funcion que gestiona la parte izquierda de &&*/
static t_ast	**front_and(t_list **token_list, int pos)
{
	t_list	**front_list;
	t_ast	**ast_left;

	if (pos == 0)
		return (NULL);
	front_list = divide_front(token_list, pos);
	if (front_list == NULL)
		return (NULL);
	ast_left = parser(front_list);
	error_tr(front_list);
	return (ast_left);
}

/*Funcion que gestiona la parte derecha de &&*/
static t_ast	**back_and(t_list **token_list, int pos)
{
	t_list	**back_list;
	t_ast	**ast_right;
	int		size;

	size = ft_lstsize(*token_list);
	if ((pos + 1) == size)
		return (NULL);
	back_list = divide_back(token_list, pos);
	if (back_list == NULL)
		return (NULL);
	ast_right = parser(back_list);
	error_tr(back_list);
	return (ast_right);
}

/*Funcion que gestiona && en pos*/
t_ast	**parser_and(t_list **token_list, int pos)
{
	t_ast	**ast_list;
	t_ast	**ast_right;
	t_ast	**ast_left;

	ast_list = create_ast(token_list, pos);
	if (ast_list == NULL)
		return (NULL);
	ast_left = front_and(token_list, pos);
	if (ast_left == NULL)
		return (error_ast(ast_list));
	*ast_list->left_list = *ast_left;
	free(ast_left);
	ast_right = back_and(token_list, pos);
	if (ast_right == NULL)
		return (error_ast(ast_list));
	*ast_list->right_ast = *ast_right;
	free(ast_right);
	return (ast_list);
}
