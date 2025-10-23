/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_lex_par_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:04:56 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 12:10:00 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crea la lista dentro de los parentesis correspondientes*/
static t_list	**lst_inside_parentheses(t_list **lst, int open, int close)
{
	t_list	**new_lst;
	t_list	*new_node;
	t_token	*new_token;
	t_token	*token;

	new_lst = (t_list **) malloc (sizeof(t_list *));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	while (open < close)
	{
		token = (t_token *)((ft_lstpos(*lst, open))->content);
		new_token = duplicate_token(token);
		if (!new_token)
			return (error_list(new_lst));
		new_node = ft_lstnew(new_token);
		if (!new_node)
			return (error_token(new_lst, new_token));
		ft_lstadd_back(new_lst, new_node);
		open++;
	}
	return (new_lst);
}

/*Funcion que encuentra la pos del ')' correspondiente*/
static int	pos_close(t_list **token_list, int open)
{
	t_type_lexer	type;
	t_list			*node;
	int				count;

	count = 1;
	open++;
	node = ft_lstpos(*token_list, open);
	while (node && count > 0)
	{
		type = ((t_token *)(node->content))->type;
		if (type == TOKEN_RPAREN)
			count++;
		if (type == TOKEN_LPAREN)
			count--;
		if (count == 0)
			return (open);
		open++;
		node = ft_lstpos(*token_list, open);
	}
	return (-1);
}

/*Funcion que crea la lista de transicion dentro del parentesis*/
t_list	**parentheses_list_tr(t_list **token_list, t_list **new, int open)
{
	t_list	**lst_aux;
	int		close;

	close = pos_close(token_list, open);
	if (close == -1)
		return (NULL);
	lst_aux = lst_inside_parentheses(token_list, open + 1, close);
	if (!lst_aux)
		return (NULL);
	if (transition_lex_par(lst_aux) == NULL)
		return (NULL);
	ft_lstadd_back(new, *lst_aux);
	free(lst_aux);
	return (new);
}
