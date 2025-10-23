/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_lex_par_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:01:29 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 13:20:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crea el nodo de transcion para los caracteres especiales*/
t_list	*special_node(t_list **lst, int pos, t_type_lexer type, int quote)
{
	t_list		*new_node;
	t_token_ast	*new_token;
	char		**str;
	char		*str_token;

	str_token = ((t_token *)((ft_lstpos(*lst, pos))->content))->value;
	str = (char **) malloc (2 * sizeof(char *));
	if (!str)
		return (NULL);
	str[0] = ft_strdup(str_token);
	str[1] = NULL;
	new_token = create_new_tr_token(str, type, 0, quote);
	if (!new_token)
	{
		free_str(str);
		return (NULL);
	}
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		free_str(str);
		delete_token_ast(new_token);
		return (NULL);
	}
	return (new_node);
}

/*Funcion que asigna el contenido a new_lst*/
t_list	**fill_new_lst(t_list **token_list, int open, int close)
{
	t_list	**new_lst;

	new_lst = (t_list **) malloc (sizeof(t_list *));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	if (start_list_tr(token_list, new_lst, open) == NULL)
	{
		error_tr(new_lst);
		return (NULL);
	}
	if (parentheses_list_tr(token_list, new_lst, open) == NULL)
	{
		error_tr(new_lst);
		return (NULL);
	}
	if (end_list_tr(token_list, new_lst, close) == NULL)
	{
		error_tr(new_lst);
		return (NULL);
	}
	return (new_lst);
}
