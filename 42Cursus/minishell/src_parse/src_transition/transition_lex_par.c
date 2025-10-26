/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_lex_par.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:37:50 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 12:39:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que encuentra el primer '(' de la lista*/
static int	find_open_parenthesis(t_list **open_list)
{
	t_token			*token;
	t_type_lexer	type;
	int				len;
	int				i;

	i = 0;
	len = ft_lstsize(*open_list);
	while (i < len)
	{
		token = (t_token *)((ft_lstpos(*open_list, i))->content);
		type = token->type;
		if (type == TOKEN_RPAREN)
			return (i);
		i++;
	}
	return (-1);
}

/*Funcion que encuentra el ')' correspondiente de la lista*/
static int	find_close_parenthesis(t_list **close_list, int pos)
{
	t_token			*token;
	t_type_lexer	type;
	int				count;
	int				len;

	count = 1;
	len = ft_lstsize(*close_list);
	while (pos < len && count >= 0)
	{
		token = (t_token *)((ft_lstpos(*close_list, pos))->content);
		type = token->type;
		if (type == TOKEN_RPAREN)
			count++;
		else if (type == TOKEN_LPAREN)
		{
			count--;
			if (count == 0)
				return (pos);
		}
		pos++;
	}
	return (-1);
}

/*Funcion que llama a transicion lexer/parser de forma recursiva
para menejar los parentesis*/
t_list	**transition_lex_par(t_list **token_list)
{
	int		open;
	int		close;
	t_list	**new_lst;

	open = find_open_parenthesis(token_list);
	if (open == -1)
	{
		make_transition(token_list);
		return (token_list);
	}
	close = find_close_parenthesis(token_list, open + 1);
	if (close == -1)
		return (error_list(token_list));
	new_lst = fill_new_lst(token_list, open, close);
	if (new_lst == NULL)
		return (error_list(token_list));
	ft_lstclear(token_list, delete_token);
	*token_list = *new_lst;
	free(new_lst);
	return (token_list);
}
