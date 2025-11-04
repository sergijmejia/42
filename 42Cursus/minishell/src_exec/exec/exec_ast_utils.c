/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti@student.42barcelon>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:15:19 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 20:11:21 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell_exec.h"
#include "env.h"
#include "exec.h"
#include "libft.h"
#include "builtins.h"
#include "exec_logic.h"
#include "exec_search.h"
#include "exec_command_utils.h"

/**
 * @brief Extracts name and value from VAR=value string.
 */
static t_pair	split_assignment(const char *str)
{
	t_pair	p;
	char	*eq;

	p.name = NULL;
	p.value = NULL;
	if (!str)
		return (p);
	eq = ft_strchr(str, '=');
	if (!eq)
		return (p);
	p.name = ft_substr(str, 0, eq - str);
	p.value = ft_strdup(eq + 1);
	if (!p.name || !p.value)
	{
		free(p.name);
		free(p.value);
		p.name = NULL;
		p.value = NULL;
	}
	return (p);
}

/**
 * @brief Handles a single assignment node.
 */
static void	handle_assignment(t_ast *node, t_exec_ctx *ctx)
{
	t_pair	p;

	if (!node || !node->value || !node->value[0])
		return ;
	p = split_assignment(node->value[0]);
	if (!p.name || !p.value)
		return ;
	if (get_env_val(*ctx->envp, p.name))
		update_env_var(ctx->envp, p.name, p.value);
	else
		add_temp_var(ctx->temp_vars, p.name, p.value);
	add_parser_tmp_var(ctx->parser_tmp_var, p.name, p.value);
	free(p.name);
	free(p.value);
}

/**
 * @brief Checks recursively if there is a command after assignment nodes.
 */
int	has_command_in_assignment(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_P_COMMAND)
		return (1);
	if (node->right_ast)
		return (has_command_in_assignment(node->right_ast));
	return (0);
}

/**
 * @brief Updates env_for_exec with VAR=value.
 */
void	update_env_with_assign(t_ast *assign, char ***env_for_exec)
{
	t_pair	p;

	p = split_assignment(assign->value[0]);
	if (p.name && p.value)
	{
		update_env_var(env_for_exec, p.name, p.value);
		free(p.name);
		free(p.value);
	}
}

/**
 * @brief Recursively processes assignment nodes.
 */
void	exec_assignment_chain(t_ast *assign, t_exec_ctx *ctx,
		char ***env_for_exec)
{
	if (!assign || assign->type != TOKEN_P_ASSIGNMENT)
		return ;
	handle_assignment(assign, ctx);
	if (*env_for_exec)
		update_env_with_assign(assign, env_for_exec);
	if (assign->right_ast
		&& assign->right_ast->type == TOKEN_P_ASSIGNMENT)
		exec_assignment_chain(assign->right_ast, ctx, env_for_exec);
}
