/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:01:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 14:20:01 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona el fallo de un token*/
t_list	**error_token(t_list **token_list, t_token *token)
{
	write(2, "Error\n", 6);
	g_exit_status = 1;
	return (clean_token(token_list, token));
}

/*Funcion que gestiona el fallo en la ampliacion o modificacion de la lista*/
t_list	**error_list(t_list **token_list)
{
	write(2, "Error\n", 6);
	g_exit_status = 1;
	return (clean_list(token_list));
}

/*Funcion que gestiona el fallo de una lista de transicion*/
t_list	**error_tr(t_list **token_list)
{
	write(2, "Error\n", 6);
	g_exit_status = 1;
	return (clean_tr(token_list));
}

/*Funcion que gestiona el fallo de un arbol*/
t_ast	**error_ast(t_ast **ast_list)
{
	write(2, "Error\n", 6);
	g_exit_status = 1;
	clean_ast(*ast_list);
	free(ast_list);
	ast_list = NULL;
	return (NULL);
}

/*Funcion que gestiona y reporta un syntax error*/
t_list	**error_syntax(t_list **token_list, int pos)
{
	int			size;
	int			len;
	t_token_ast	*token_tr;
	char		*str_error;
	char		*aux;

	aux = ft_strdup("minishell: syntax error near unexpected token \'");
	size = ft_lstsize(*token_list);
	if (pos == size)
		str_error = ft_strjoin(aux, "newline\'\n");
	else
	{
		token_tr = (t_token_ast *)((ft_lstpos(*token_list, pos))->content);
		str_error = ft_strjoin(aux, (token_tr->value)[0]);
		free(aux);
		aux = str_error;
		str_error = ft_strjoin(aux, "\'\n");
	}
	len = (int) ft_strlen(str_error);
	write(2, str_error, len);
	g_exit_status = 2;
	free(aux);
	free(str_error);
	return (clean_tr(token_list));
}
