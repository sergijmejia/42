/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:44:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 16:24:13 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que copia el str del token_ast al ast*/
static char	**copy_str(t_token_ast *token_ast)
{
	char	**new_str;
	char	**str;
	int		len;
	int		i;

	len = calculate_strlen(token_ast);
	if (len == -1)
		return (NULL);
	str = (char **)(token_ast->value);
	new_str = (char **) malloc ((len + 1) * sizeof(char *));
	if (new_str == NULL)
		return (NULL);
	new_str[len] = NULL;
	i = 0;
	while (i < len)
	{
		new_str[i] = strdup(str[i]);
		if (new_str[i] == NULL)
		{
			free_str(new_str);
			return (NULL);
		}
		i++;
	}
	return (new_str);
}

/*Funcion que define el type de ast*/
static int	copy_type(t_token_ast *token_ast)
{
	t_type_tr	type;
	int			new_type;

	type = token_ast->type;
	if (type <= 9)
		new_type = type;
	else if (type == 11)
		new_type = 10;
	else
		new_type = -1;
	return (new_type);
}

/*Funcion que crea el ast equivalente a pos*/
t_ast	**create_ast(t_list **token_list, int pos)
{
	t_ast		**ast_list;
	t_ast		*ast_node;
	t_token_ast	*token_ast;
	t_list		*node;

	ast_list = (t_ast **) malloc (sizeof(t_ast *));
	if (ast_list == NULL)
		return (NULL);
	node = ft_lstpos(*token_list, pos);
	if (node == NULL)
		return (error_ast(ast_list));
	token_ast = (t_token_ast *)(node->content);
	ast_node = (t_ast *) malloc (sizeof(t_ast));
	if (ast_node == NULL)
		return (error_ast(ast_list));
	*ast_list = ast_node;
	ast_node->left_ast = NULL;
	ast_node->right_ast = NULL;
	ast_node->value = copy_str(token_ast);
	ast_node->type = copy_type(token_ast);
	if ((ast_node->value == NULL) || (((int)(ast_node->type)) == -1))
		return (error_ast(ast_list));
	ast_node->wildcard = token_ast->wildcard;
	return (ast_list);
}
