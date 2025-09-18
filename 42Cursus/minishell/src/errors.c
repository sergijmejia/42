/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:01:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/18 17:05:35 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona la eliminacion de un t_token*/
void	delete_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

/*Funcion que libera memoria de un puntero char doble*/
char	**free_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (NULL);
}

/*Funcion que gestiona la eliminacion de un t_token_ast*/
void	delete_token_ast(void *content)
{
	t_token_ast	*token;

	token = (t_token_ast *)content;
	free_str(token->value);
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
	free(token_list);
	token_list = NULL;
	return (NULL);
}

/*Funcion que gestiona el fallo en la modificacion de una lista de transicion*/
t_list	**error_tr(t_list **token_list)
{
	ft_lstclear(token_list, delete_token_ast);
	free(token_list);
	token_list = NULL;
	return (NULL);
}
