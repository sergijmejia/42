/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_selection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 08:52:10 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/14 13:05:41 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona el loop de assignment_selection*/
static int	assignment_selection_loop(t_token *token, int *poss_assignment)
{
	if (*poss_assignment)
	{
		if (token->type == TOKEN_ASSIGNMENT_CANDIDATE)
			token->type = TOKEN_ASSIGNMENT_WORD;
		if (token->type == TOKEN_WORD)
			*poss_assignment = 0;
	}
	else
	{
		if (token->type == TOKEN_ASSIGNMENT_CANDIDATE)
			token->type = TOKEN_WORD;
		if (token->type == TOKEN_PIPE)
			*poss_assignment = 1;
		if (token->type == TOKEN_AND)
			*poss_assignment = 1;
		if (token->type == TOKEN_OR)
			*poss_assignment = 1;
	}
	return (0);
}

/*Funcion que selecciona los TOKEN_ASSIGNMENT_WORD*/
t_list	**assignment_selection(t_list **token_list)
{
	t_list	*lst;
	t_token	*token;
	int		possible_assignment;
	int		i;

	possible_assignment = 1;
	if (token_list == NULL || *token_list == NULL)
		return (token_list);
	i = 0;
	lst = ft_lstpos(*token_list, i);
	while (lst != NULL)
	{
		token = (t_token *)(lst->content);
		assignment_selection_loop(token, &possible_assignment);
		i++;
		lst = ft_lstpos(*token_list, i);
	}
	return (token_list);
}
