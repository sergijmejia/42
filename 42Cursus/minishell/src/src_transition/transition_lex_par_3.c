/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_lex_par_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:08:45 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 11:55:31 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crea la lista hasta '('*/
static t_list	**lst_until_open(t_list **token_list, int open)
{
	int		i;
	t_list	**new_lst;
	t_list	*new_node;
	t_token	*new_token;
	t_token	*token;

	i = 0;
	new_lst = (t_list **) malloc (sizeof(t_list *));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	while (i <= open)
	{
		token = (t_token *)((ft_lstpos(*token_list, i))->content);
		new_token = duplicate_token(token);
		if (!new_token)
			return (error_list(new_lst));
		new_node = ft_lstnew(new_token);
		if (!new_node)
			return (error_token(new_lst, new_token));
		ft_lstadd_back(new_lst, new_node);
		i++;
	}
	return (new_lst);
}

/*Funcion que gestiona el loop de make_transition*/
static t_list	*make_transition_loop(t_list **token_list, int *pos)
{
	int				quote;
	t_type_lexer	type;
	t_list			*new_node;

	type = ((t_token *)((ft_lstpos(*token_list, *pos))->content))->type;
	quote = ((t_token *)((ft_lstpos(*token_list, *pos))->content))->quote;
	if (type >= 4)
	{
		new_node = special_node(token_list, *pos, type, quote);
		(*pos)++;
	}
	else
		new_node = command_node(token_list, pos, quote);
	return (new_node);
}

/*Funcion que hace crea la lista tr_lexer_parser*/
t_list	**make_transition(t_list **token_list)
{
	t_list			**new_lst;
	t_list			*new_node;
	int				pos;
	int				len;

	pos = 0;
	len = ft_lstsize(*token_list);
	new_lst = (t_list **) malloc (sizeof(t_list *));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	while (pos < len)
	{
		new_node = make_transition_loop(token_list, &pos);
		if (!new_node)
			return (error_tr(new_lst));
		ft_lstadd_back(new_lst, new_node);
	}
	ft_lstclear(token_list, delete_token);
	*token_list = *new_lst;
	free(new_lst);
	return (token_list);
}

/*Funcion que crea la lista de transicion hasta '('*/
t_list	**start_list_tr(t_list **token_list, t_list **new_list, int open)
{
	t_list	**lst_aux;

	lst_aux = lst_until_open(token_list, open);
	if (!lst_aux)
		return (NULL);
	if (make_transition(lst_aux) == NULL)
		return (error_list(lst_aux));
	ft_lstadd_back(new_list, *lst_aux);
	free(lst_aux);
	return (new_list);
}
