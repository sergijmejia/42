/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:01:11 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/05 14:19:13 by smejia-a         ###   ########.fr       */
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

/*Funcion que gestiona el fallo de un token*/
t_list	**error_token(t_list **token_list, t_token *token)
{
	delete_token(token);
	return (error_list(token_list));
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

/*Funcion que gestiona el fallo en la ampliacion o modificacion de parser*/
t_ast	**error_ast(t_ast **ast_list)
{
	astdel(*ast_list);
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
	if (pos == size - 1)
		str_error = ft_strjoin(aux, "newline\'\n");
	else
	{
		token_tr = (t_token_ast *) ((ft_lstpos(*token_list, pos))->content);
		str_error = ft_strjoin(aux, (token_tr->value)[0]);
		free(aux);
		aux = str_error;
		str_error = ft_strjoin(aux, "\'\n");
	}
	len = (int) ft_strlen(str_error);
	write(2, str_error, len);
	//write(2, "\n", 1);
	free(aux);
	free(str_error);
	return (error_tr(token_list));
}
