/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:51:57 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/02 15:24:55 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Imprime por pantalla un ast en el orden en que se ejecutan*/
void	print_ast(t_ast *ast_list)
{
	t_ast	*ast_left;
	t_ast	*ast_right;
	char	**str;
	int		len;
	int		i;

	if (ast_list == NULL)
	{
		ft_printf("(NULL)\n");
		return ;
	}
	ast_left = ast_list->left_ast;
	ast_right = ast_list->right_ast;
	if (ast_left != NULL)
		print_ast(ast_left);
	if (ast_right != NULL)
		print_ast(ast_right);
	str = (char **)(ast_list->value);
	len = 0;
	while (str[len])
		len++;
	i = 0;
	while (i < len)
	{
		ft_printf("%s", str[i]);
		i++;
		if (i != len)
			ft_printf(", ");
	}
	ft_printf("    (%d)\n", ast_list->type);
	return ;
}
