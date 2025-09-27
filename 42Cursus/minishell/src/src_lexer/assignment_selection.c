/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_selection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 08:52:10 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/17 13:58:11 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que selecciona los TOKEN_ASSIGNMENT_WORD*/
t_list	**assignment_selection(t_list **token_list)
{
	t_list	*lst;
	t_token	*token;
	int		possible_assignment;
	int		i;

	possible_assignment = 1;
	if (token_list == NULL)
		return (token_list);
	i = 0;
	lst = ft_lstpos(*token_list, i);
	token = (t_token *)(lst->content);
	while (lst != NULL)
	{
		token = (t_token *)(lst->content);
		if (possible_assignment)
		{
			if (token->type == TOKEN_ASSIGNMENT_CANDIDATE)
				token->type = TOKEN_ASSIGNMENT_WORD;
			if (token->type == TOKEN_WORD)
				possible_assignment = 0;
		}
		else
		{
			if (token->type == TOKEN_ASSIGNMENT_CANDIDATE)
				token->type = TOKEN_WORD;
			if (token->type == TOKEN_PIPE)
				possible_assignment = 1;
			if (token->type == TOKEN_AND)
				possible_assignment = 1;
			if (token->type == TOKEN_OR)
				possible_assignment = 1;
		}
		i++;
		lst = ft_lstpos(*token_list, i);
	}
	return (token_list);
}
