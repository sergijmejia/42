/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:15:52 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 14:16:56 by smejia-a         ###   ########.fr       */
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

/*Funcion que gestiona la eliminacio de un t_ast*/
void	delete_ast(void *content)
{
	t_ast	*node;

	node = (t_ast *)content;
	free_str(node->value);
	free(node);
	node = NULL;
}

/*Funcion que elimina el ast a partir de un nodo especifico*/
void	astdel(t_ast *ast_list)
{
	if (ast_list == NULL)
		return ;
	if (ast_list->left_ast != NULL)
		astdel(ast_list->left_ast);
	if (ast_list->right_ast != NULL)
		astdel(ast_list->right_ast);
	delete_ast(ast_list);
	ast_list = NULL;
}
