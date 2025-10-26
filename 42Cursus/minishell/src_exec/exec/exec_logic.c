/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:54:12 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/20 11:24:07 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "exec.h"
#include "minishell_exec.h"
#include "exec_logic.h"

/**
 * @brief Executes a logical AND (&&) node.
 *
 * Executes the left AST node, if successful executes the right AST node.
 *
 * @param node AST node of type TOKEN_P_AND
 * @param temp_vars Temporary environment variable list
 * @param envp Pointer to the environment array
 *
 * @note Updates g_exit_status.
 */
void	exec_and(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	if (!node)
	{
		g_exit_status = 1;
		return ;
	}
	exec_ast(node->left_ast, temp_vars, envp, parser_tmp_var);
	if (g_exit_status == 0)
		exec_ast(node->right_ast, temp_vars, envp, parser_tmp_var);
}

/**
 * @brief Executes a logical OR (||) node.
 *
 * Executes the left AST node, if it fails executes the right AST node.
 *
 * @param node AST node of type TOKEN_P_OR
 * @param temp_vars Temporary environment variable list
 * @param envp Pointer to the environment array
 *
 * @note Updates g_exit_status.
 */
void	exec_or(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	if (!node)
	{
		g_exit_status = 1;
		return ;
	}
	exec_ast(node->left_ast, temp_vars, envp, parser_tmp_var);
	if (g_exit_status != 0)
		exec_ast(node->right_ast, temp_vars, envp, parser_tmp_var);
}

/**
 * @brief Forks and executes a parenthesis AST node.
 *
 * Child restores default signals (SIGINT, SIGQUIT) and executes inner AST.
 *
 * @param node AST node of type TOKEN_P_PARENTHESIS
 * @param temp_vars Temporary environment variable list
 * @param envp Pointer to the environment array
 *
 * @note Updates g_exit_status.
 */
void	exec_parenthesis(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	pid_t	pid;
	int		status;

	if (!node)
	{
		g_exit_status = 1;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_ast(node->left_ast, temp_vars, envp, parser_tmp_var);
		_exit(g_exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	else
		g_exit_status = 1;
}
