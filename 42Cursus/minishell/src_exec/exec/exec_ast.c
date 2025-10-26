/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti@student.42barcelon>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:15:19 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/26 14:00:55 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell_exec.h"
#include "env.h"
#include "exec.h"
#include "exec_logic.h"
#include "exec_search.h"
#include "exec_command_utils.h"
#include "builtins.h"
#include "libft.h"

/**
 * @brief Extracts name and value from VAR=value string.
 *
 * @param str String of the form VAR=VALUE
 * @return Struct with name and value (both NULL if error)
 */
static t_pair split_assignment(const char *str)
{
    t_pair p;
    char *eq;

    p.name = NULL;
    p.value = NULL;
    if (!str)
        return p;
    eq = ft_strchr(str, '=');
    if (!eq)
        return p;
    p.name = ft_substr(str, 0, eq - str);
    p.value = ft_strdup(eq + 1);
    if (!p.name || !p.value)
    {
        free(p.name);
        free(p.value);
        p.name = NULL;
        p.value = NULL;
    }
    return p;
}

/**
 * @brief Handles a single assignment node.
 *
 * Adds the variable to temp_vars (shell local variables) or updates envp
 * if it already exists. Used for assignments without command.
 *
 * @param node AST node of type TOKEN_P_ASSIGNMENT
 * @param temp_vars Pointer to the list of temporary variables
 * @param parser_tmp_var Parser's temporary variable table (optional)
 * @param envp Pointer to the shell global environment
 */
static void handle_assignment(t_ast *node, t_temp_lst_exec **temp_vars,
        t_list **parser_tmp_var, char ***envp)
{
    t_pair p;

    if (!node || !node->value || !node->value[0])
        return;

    p = split_assignment(node->value[0]);
    if (!p.name || !p.value)
        return ;

    if (get_env_val(*envp, p.name))
        update_env_var(envp, p.name, p.value);
    else
        add_temp_var(temp_vars, p.name, p.value);
	
    add_parser_tmp_var(parser_tmp_var, p.name, p.value);

    free(p.name);
    free(p.value);
}

/**
 * @brief Forks a child process and executes a command with a given environment.
 *
 * @param node AST node representing the command
 * @param env_for_exec Environment array to use for execve
 */
static void fork_and_exec(t_ast *node, char **env_for_exec)
{
    pid_t pid;

    if (!node || !env_for_exec)
        return;

    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork failed");
        free_envp(env_for_exec);
        g_exit_status = 1;
        return;
    }

    if (pid == 0)
    {
        // Child
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        if (node->value && node->value[0])
            _exit(find_and_exec(node->value, env_for_exec));
        else
            _exit(0);
    }

    // Parent
    wait_child_and_update_status(pid, env_for_exec);
}

/**
 * @brief Executes simple AST nodes: assignments, commands, pipes, redirections.
 *
 * Supports:
 *  - Multiple consecutive assignment nodes with or without command.
 *  - Assignments without command are stored in temp_vars (shell local variables).
 *  - Assignments with command are applied to env_for_exec (temporary environment).
 *
 * @param node AST node
 * @param temp_vars Pointer to temporary shell variable list
 * @param envp Pointer to global environment
 * @param parser_tmp_var Parser's temporary variable table
 */
static void exec_ast_simple(t_ast *node, t_temp_lst_exec **temp_vars,
        char ***envp, t_list **parser_tmp_var)
{
    if (!node)
    {
        g_exit_status = 0;
        return;
    }

    if (node->type == TOKEN_P_ASSIGNMENT)
    {
        t_ast *assign = node;
        char **env_for_exec = NULL;
        int has_command = 0;

        // Check if there's a command after assignments
        t_ast *tmp = assign;
        while (tmp)
        {
            if (tmp->type == TOKEN_P_COMMAND)
            {
                has_command = 1;
                break;
            }
            tmp = tmp->right_ast;
        }

        // If there's a command, create temporary environment
        if (has_command)
            env_for_exec = build_envp(*temp_vars, *envp);

        // Apply all consecutive assignments
        while (assign && assign->type == TOKEN_P_ASSIGNMENT)
        {
            handle_assignment(assign, temp_vars, parser_tmp_var, envp);

            if (env_for_exec)
            {
                t_pair p = split_assignment(assign->value[0]);
                if (p.name && p.value)
                {
                    update_env_var(&env_for_exec, p.name, p.value);
                    free(p.name);
                    free(p.value);
                }
            }

            assign = assign->right_ast;
        }

        // Execute command if exists
        if (has_command && assign && assign->type == TOKEN_P_COMMAND)
            fork_and_exec(assign, env_for_exec);

        if (env_for_exec)
            free_envp(env_for_exec);

        g_exit_status = 0;
    }
    else if (node->type == TOKEN_P_COMMAND)
        exec_command(node, temp_vars, envp, parser_tmp_var);
    else if (node->type == TOKEN_P_PIPE)
        exec_pipe(node, temp_vars, envp, parser_tmp_var);
    else if (node->type == TOKEN_P_GT || node->type == TOKEN_P_DOUBLE_GT
        || node->type == TOKEN_P_LT || node->type == TOKEN_P_DOUBLE_LT)
        exec_redir(node, temp_vars, envp, parser_tmp_var);
    else
    {
        ft_putendl_fd("minishell: syntax error: unsupported construct", 2);
        g_exit_status = 1;
    }
}

/**
 * @brief Executes an AST node by dispatching according to type.
 *
 * Handles logical AND/OR and parentheses specially.
 *
 * @param node AST node
 * @param temp_vars Temporary variable list
 * @param envp Global environment
 * @param parser_tmp_var Parser's temporary variable table
 */
void exec_ast(t_ast *node, t_temp_lst_exec **temp_vars,
        char ***envp, t_list **parser_tmp_var)
{
    if (!node)
    {
        g_exit_status = 0;
        return;
    }
    if (node->type == TOKEN_P_AND)
        exec_and(node, temp_vars, envp, parser_tmp_var);
    else if (node->type == TOKEN_P_OR)
        exec_or(node, temp_vars, envp, parser_tmp_var);
    else if (node->type == TOKEN_P_PARENTHESIS)
        exec_parenthesis(node, temp_vars, envp, parser_tmp_var);
    else
        exec_ast_simple(node, temp_vars, envp, parser_tmp_var);
}
