/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:16:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 13:18:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona el if (i != size - 1) del loop en find_direction*/
static t_list	**find_direction_conditional(t_list **lst, int pos, int type)
{
	t_token			*token;

	token = (t_token *)((ft_lstpos(*lst, pos + 1))->content);
	if (token == NULL)
		return (NULL);
	if (type >= 5 && type <= 7)
	{
		type = token->type;
		if (type == 0 || type == 2 || type == 3 || type == 9)
			token->type = TOKEN_REDIRECTION_WORD;
	}
	else if (type == 8)
	{
		type = token->type;
		if (type == 0 || type == 2 || type == 3 || type == 9)
			token->type = TOKEN_REDIRECTION_HEREDOC;
	}
	return (lst);
}

/*Funcion que asigna el type a los nodos de redireccion*/
t_list	**find_redirection(t_list **token_list)
{
	int				size;
	int				i;
	t_token			*token;
	t_type_lexer	type;

	size = ft_lstsize(*token_list);
	i = 0;
	while (i < size)
	{
		token = (t_token *)((ft_lstpos(*token_list, i))->content);
		if (token == NULL)
			return (error_list(token_list));
		type = token->type;
		if (i != size - 1)
		{
			if (find_direction_conditional(token_list, i, type) == NULL)
				return (error_list(token_list));
		}
		i++;
	}
	return (token_list);
}
