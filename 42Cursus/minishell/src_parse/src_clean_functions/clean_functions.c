/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:04:57 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 14:15:33 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona la liberacion de memoria de un token*/
t_list	**clean_token(t_list **token_list, t_token *token)
{
	delete_token(token);
	return (clean_list(token_list));
}

/*Funcion que gestiona la liberacion de memoria de la lista*/
t_list	**clean_list(t_list **token_list)
{
	ft_lstclear(token_list, delete_token);
	free(token_list);
	token_list = NULL;
	return (NULL);
}

/*Funcion que gestiona la liberacion de memoria de una lista de transicion*/
t_list	**clean_tr(t_list **token_list)
{
	ft_lstclear(token_list, delete_token_ast);
	free(token_list);
	token_list = NULL;
	return (NULL);
}

/*Funcion que gestiona la liberacion de memoria de un arbol*/
t_ast	*clean_ast(t_ast *ast_list)
{
	astdel(ast_list);
	ast_list = NULL;
	return (NULL);
}

/*Libera un elemento de la tabla tmp_lst*/
void	free_tmp_var_p(void *content)
{
	t_temp_lst	*tmp_lst;

	tmp_lst = (t_temp_lst *)content;
	free(tmp_lst->name);
	free(tmp_lst->value);
	free(tmp_lst);
}
