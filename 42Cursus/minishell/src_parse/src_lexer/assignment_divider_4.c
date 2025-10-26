/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_divider_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:49:36 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 11:50:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crea un nuevo nodo*/
t_list	*create_node(char *str, int start, int end, int type)
{
	char	*str_token;
	t_token	*token;
	t_list	*new_node;

	str_token = (char *) malloc (sizeof(char) * (end - start + 2));
	if (!str_token)
		return (NULL);
	token = (t_token *) malloc (sizeof (t_token));
	if (!token)
	{
		free (str_token);
		return (NULL);
	}
	ft_strlcpy(str_token, &str[start], end - start + 2);
	token->value = str_token;
	if (type == 0)
		token->type = TOKEN_WORD;
	if (type == 9)
		token->type = TOKEN_ASSIGNMENT_CANDIDATE;
	token->finished = 0;
	token->quote = 0;
	new_node = ft_lstnew(token);
	if (!new_node)
		delete_token(token);
	return (new_node);
}
