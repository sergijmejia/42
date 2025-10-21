/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_divider_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:54:27 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 13:56:04 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crear una lueva lista para agregarla a lst original*/
static t_list	*create_new_lst_token(t_list *token, int pos_space)
{
	int		len_str;
	char	*str;
	t_token	*new_token;
	t_list	*new_list_token;

	len_str = (int) ft_strlen(((t_token *)(token->content))->value);
	str = ft_substr(((t_token *)(token->content))->value, pos_space, len_str);
	if (!str)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free (str);
		return (NULL);
	}
	new_token->value = str;
	new_token->type = TOKEN_WORD;
	new_token->finished = 0;
	new_list_token = ft_lstnew(new_token);
	if (!new_list_token)
		delete_token(new_token);
	return (new_list_token);
}

/*Funcion que crea el nodo que contiene el string previo al divisor*/
t_list	**node_before_div(t_list **token_list, int i, int pos)
{
	t_list	*first_token;
	t_list	*new_list_token;
	char	*str;

	first_token = ft_lstpos(*token_list, i);
	if (!first_token)
		return (NULL);
	new_list_token = create_new_lst_token(first_token, pos);
	if (!new_list_token)
		return (NULL);
	str = ft_substr(((t_token *)(first_token->content))->value, 0, pos);
	if (!str)
	{
		ft_lstclear(&new_list_token, delete_token);
		return (NULL);
	}
	free(((t_token *)(first_token->content))->value);
	((t_token *)(first_token->content))->value = str;
	((t_token *)(first_token->content))->type = check_type(first_token);
	ft_lstadd_pos(token_list, new_list_token, i + 1);
	return (token_list);
}
