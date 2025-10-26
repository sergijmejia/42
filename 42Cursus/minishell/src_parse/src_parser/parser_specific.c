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
