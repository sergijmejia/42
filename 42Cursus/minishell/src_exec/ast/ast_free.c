/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:01:14 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 03:46:31 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "minishell.h"
#include "utils.h"

/**
 * @brief Frees an AST node and all its children recursively.
 *
 * Uses ft_free_split to safely free the node->value array.
 *
 * @param node AST node to free
 */
void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left_ast);
	free_ast(node->right_ast);
	free_split(node->value);
	free(node);
}
