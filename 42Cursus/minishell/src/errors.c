/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:01:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/12 11:53:19 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona la eliminacion de un token*/
void	delete_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

/*Funcion que gestiona el fallo de un token*/
t_list	**error_token(t_list **token_list, t_token *token)
{
	delete_token(token);
	ft_lstclear(token_list, delete_token);
	return (NULL);
}

/*Funcion que gestiona el fallo en la ampliacion o modificacion de la lista*/
t_list	**error_list(t_list **token_list)
{
	ft_lstclear(token_list, delete_token);
	return (NULL);
}
