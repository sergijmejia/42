/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:52:25 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 01:52:26 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell_exec.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/**
 * @brief Open a file according to redirection type.
 *
 * @param filename File name to open.
 * @param type Token type (>, >>, <).
 * @return File descriptor or -1 on error.
 */
int	open_redir_file(char *filename, int type)
{
	int	flags;

	if (!filename)
		return (-1);
	if (type == TOKEN_P_GT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (type == TOKEN_P_DOUBLE_GT)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (type == TOKEN_P_LT)
		flags = O_RDONLY;
	else
		return (-1);
	return (open(filename, flags, 0644));
}

/**
 * @brief Handle a heredoc node: search left first, then right.
 */
static char	*get_from_heredoc(t_ast *node)
{
	char	*name;

	if (!node)
		return (NULL);
	if (node->left_ast)
	{
		name = get_redir_filename_from_node(node->left_ast);
		if (name)
			return (name);
	}
	if (node->right_ast)
		return (get_redir_filename_from_node(node->right_ast));
	return (NULL);
}

/**
 * @brief Handle a normal redirection node: filename lives in right branch.
 */
static char	*get_from_normal_redir(t_ast *node)
{
	if (!node)
		return (NULL);
	if (node->right_ast)
		return (get_redir_filename_from_node(node->right_ast));
	return (NULL);
}

/**
 * @brief Return node value if present, otherwise search both children.
 */
static char	*get_value_or_search(t_ast *node)
{
	char	*name;

	if (!node)
		return (NULL);
	if (node->value && node->value[0] && node->value[0][0] != '\0')
		return (node->value[0]);
	if (node->left_ast)
	{
		name = get_redir_filename_from_node(node->left_ast);
		if (name)
			return (name);
	}
	if (node->right_ast)
		return (get_redir_filename_from_node(node->right_ast));
	return (NULL);
}

/**
 * @brief Recursively find the filename in an AST node.
 *
 * Behavior:
 *  - For heredoc (<<) search left first, then right.
 *  - For normal redirs (>, >>, <) search right.
 *  - Otherwise return a node->value[0] if present or search both children.
 */
char	*get_redir_filename_from_node(t_ast *node)
{
	if (!node)
		return (NULL);
	if (node->type == TOKEN_P_DOUBLE_LT)
		return (get_from_heredoc(node));
	if (node->type == TOKEN_P_GT || node->type == TOKEN_P_DOUBLE_GT
		|| node->type == TOKEN_P_LT)
		return (get_from_normal_redir(node));
	return (get_value_or_search(node));
}
