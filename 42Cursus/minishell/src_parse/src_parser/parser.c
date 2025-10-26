/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:32:23 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 16:23:32 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que encuentra la posicion de las redirecciones siguiendo el orden 
de jerarquia*/
static int	find_specific_redirection(t_list **token_list)
{
	int	pos;

	pos = find_specific(token_list, 2);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 3);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 4);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 5);
	if (pos >= 0)
		return (pos);
	return (-1);
}

/*Funcion que encuentra la posicion del siguiente special siguiendo orden 
de jerarquia*/
static int	find_next_special(t_list **token_list)
{
	int	pos;

	pos = find_specific(token_list, 7);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 8);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 1);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 6);
	if (pos >= 0)
		return (pos);
	pos = find_specific_redirection(token_list);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 11);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 0);
	if (pos >= 0)
		return (pos);
	pos = find_specific(token_list, 9);
	return (pos);
}

/*Funcion que llama al correspondiente parser en base al tipo*/
static t_ast	**create_ast_list(t_list **token_list, int pos, int type)
{
	t_ast	**new_ast;

	new_ast = NULL;
	if ((type >= 0 && type <= 8) || type == 11)
		new_ast = parser_specific(token_list, pos);
	else if (type == 9)
		new_ast = parser_parenthesis(token_list);
	return (new_ast);
}

/*Funcion que genera el ast que sera utilizado por el executor*/
t_ast	**parser(t_list **token_list)
{
	int		pos;
	int		size;
	int		type;
	t_ast	**ast_list;

	if (token_list == NULL)
		return (NULL);
	size = ft_lstsize(*token_list);
	if (size == 0)
	{
		ast_list = (t_ast **) malloc (sizeof(t_ast *));
		if (ast_list == NULL)
			return (NULL);
		*ast_list = NULL;
		return (ast_list);
	}
	pos = find_next_special(token_list);
	if (pos == size)
		return (NULL);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos))->content))->type;
	ast_list = create_ast_list(token_list, pos, type);
	return (ast_list);
}
