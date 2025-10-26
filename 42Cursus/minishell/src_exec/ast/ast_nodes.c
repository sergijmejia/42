/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:01:03 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 03:46:01 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_exec.h"
#include "minishell.h"
#include "libft.h"
#include "utils.h"
#include "dup_argv.h"

/**
 * @brief Creates a command AST node, duplicating argv strings.
 *
 * @param argv Array of command arguments (NULL-terminated)
 * @return Pointer to the AST node or NULL if malloc fails
 */
t_ast	*new_command(char **argv)
{
	t_ast	*node;

	if (!argv)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->value = dup_argv(argv);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->type = TOKEN_P_COMMAND;
	node->left_ast = NULL;
	node->right_ast = NULL;
	node->wildcard = 0;
	return (node);
}

/**
 * @brief Creates a binary AST node (pipe, AND, OR).
 *
 * @param type Type of binary node
 * @param left Left child AST node
 * @param right Right child AST node
 * @return Pointer to the AST node or NULL if malloc fails
 */
t_ast	*new_binary_op(enum e_type_parser type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = NULL;
	node->left_ast = left;
	node->right_ast = right;
	node->wildcard = 0;
	return (node);
}

/**
 * @brief Duplicates filename into node->value as {filename, NULL}.
 *
 * @param node Target AST node
 * @param filename Redirection target
 * @return 1 on success, 0 on failure
 */
static int	assign_redir_value(t_ast *node, char *filename)
{
	node->value = malloc(sizeof(char *) * 2);
	if (!node->value)
		return (0);
	node->value[0] = ft_strdup(filename);
	if (!node->value[0])
	{
		free(node->value);
		return (0);
	}
	node->value[1] = NULL;
	return (1);
}

/**
 * @brief Creates a redirection AST node (> >> < <<).
 *
 * @param type Type of redirection node
 * @param cmd Command AST node
 * @param filename File name or heredoc content
 * @return Pointer to the AST node or NULL if malloc fails
 */
t_ast	*new_redirection(enum e_type_parser type, t_ast *cmd, char *filename)
{
	t_ast	*node;

	if (!cmd || !filename)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	if (!assign_redir_value(node, filename))
	{
		free(node);
		return (NULL);
	}
	node->type = type;
	node->left_ast = cmd;
	node->right_ast = NULL;
	node->wildcard = 0;
	return (node);
}

/**
 * @brief Creates an assignment AST node (NAME=VALUE).
 *
 * @param assign_str Assignment string
 * @return Pointer to the AST node or NULL if malloc fails
 */
t_ast	*new_assignment(char *assign_str)
{
	t_ast	*node;
	char	*tmp[2];

	if (!assign_str)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	tmp[0] = assign_str;
	tmp[1] = NULL;
	node->value = dup_argv(tmp);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->type = TOKEN_P_ASSIGNMENT;
	node->left_ast = NULL;
	node->right_ast = NULL;
	node->wildcard = 0;
	return (node);
}
