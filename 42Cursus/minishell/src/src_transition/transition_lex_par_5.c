/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_lex_par_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:21:55 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 12:22:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crea la lista desde '('*/
static t_list	**lst_until_end(t_list **token_list, int close)
{
	t_list	**new_lst;
	t_list	*new_node;
	t_token	*new_token;
	t_token	*token;
	int		len;

	new_lst = (t_list **) malloc (sizeof(t_list *));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	len = ft_lstsize(*token_list);
	while (close < len)
	{
		token = (t_token *)((ft_lstpos(*token_list, close))->content);
		new_token = duplicate_token(token);
		if (!new_token)
			return (error_list(new_lst));
		new_node = ft_lstnew(new_token);
		if (!new_node)
			return (error_token(new_lst, new_token));
		ft_lstadd_back(new_lst, new_node);
		close++;
	}
	return (new_lst);
}

/*Funcion que crea la lista de transicion desde ')' hasta el final*/
t_list	**end_list_tr(t_list **token_list, t_list **new_list, int close)
{
	t_list			**lst_aux;
	t_list			*new_node;
	t_type_lexer	type;
	int				quote;

	lst_aux = lst_until_end(token_list, close + 1);
	if (!lst_aux)
		return (NULL);
	type = ((t_token *)((ft_lstpos(*token_list, close))->content))->type;
	quote = ((t_token *)((ft_lstpos(*token_list, close))->content))->quote;
	new_node = special_node(token_list, close, type, quote);
	if (!new_node)
		return (error_list(lst_aux));
	ft_lstadd_back(new_list, new_node);
	if (transition_lex_par(lst_aux) == NULL)
		return (NULL);
	ft_lstadd_back(new_list, *lst_aux);
	free(lst_aux);
	return (new_list);
}
