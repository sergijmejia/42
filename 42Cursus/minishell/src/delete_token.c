/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:01:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/18 18:26:01 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona la eliminacion de un token*/
void	delete_token(t_token *token)
{
	free(token->value);
	free(token);
}

/*Funcion que gestiona el fallo de un token*/
void	error_token(t_list **token_list, char *str)
{
	ft_lstclear(token_list, delete_token);
	free(str);
	exit(EXIT_FAILURE);
}

/*Funcion que gestiona el fallo de un string de un token*/
void	error_token_value(t_list **token_list, t_token token, char *str)
{
	delete_token(token);
	error_token(token_list, str);
}

/*Funcion que gestiona la ampliacion o modificacion de la lista*/
void	error_list(t_list **token_list)
{
	ft_lstclear(token_list, delete_token);
	exit(EXIT_FAILURE);
}
