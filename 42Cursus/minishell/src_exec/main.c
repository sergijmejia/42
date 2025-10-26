/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:00:00 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 03:42:54 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"
#include "minishell_exec.h"
#include "env.h"
#include "exec.h"
#include "ast.h"
#include "libft.h"

int g_exit_status = 0;

static char **init_env(char **envp)
{
    char **my_envp = clone_envp(envp);
    int has_path = 0;

    if (!my_envp)
        return NULL;

    for (int i = 0; my_envp[i]; i++)
    {
        if (!ft_strncmp(my_envp[i], "PATH=", 5))
        {
            has_path = 1;
            break;
        }
    }
    if (!has_path)
        export_assignment("PATH=/usr/bin:/bin", &my_envp);

    return my_envp;
}

int main(int argc, char **argv, char **envp)
{
    t_temp_lst_exec *temp_vars = NULL;
    char **my_envp = init_env(envp);

    (void)argc;
    (void)argv;

    if (!my_envp)
    {
        perror("Failed to clone environment");
        return 1;
    }

    /*----------------- SIMPLE COMMAND -----------------*/
    printf("\n=== TEST: SIMPLE COMMAND ===\n");
    t_ast *node = new_command((char*[]){"echo", "Hello simple!", NULL});
    exec_ast(node, &temp_vars, &my_envp);
    free_ast(node);

    /*----------------- PIPELINE -----------------*/
    printf("\n=== TEST: PIPELINE ===\n");
    t_ast *ls = new_command((char*[]){"ls", "-1", NULL});
    t_ast *grep = new_command((char*[]){"grep", ".c", NULL});
    t_ast *pipe_node = new_binary_op(TOKEN_P_PIPE, ls, grep);
    exec_ast(pipe_node, &temp_vars, &my_envp);
    free_ast(pipe_node);

    /*----------------- REDIRECTION > out.txt -----------------*/
    printf("\n=== TEST: REDIRECTION > out.txt ===\n");
    t_ast *echo1 = new_command((char*[]){"echo", "Hello out.txt!", NULL});
    t_ast *redir1 = new_redirection(TOKEN_P_GT, echo1, "out.txt");
    exec_ast(redir1, &temp_vars, &my_envp);
    free_ast(redir1);
    printf("Contents of out.txt:\n");
    system("cat out.txt");

    /*----------------- REDIRECTION >> append.txt -----------------*/
    printf("\n=== TEST: REDIRECTION >> append.txt ===\n");
    t_ast *echo2 = new_command((char*[]){"echo", "Hello append!", NULL});
    t_ast *redir2 = new_redirection(TOKEN_P_DOUBLE_GT, echo2, "append.txt");
    exec_ast(redir2, &temp_vars, &my_envp);
    free_ast(redir2);
    // Append multiple times for testing
    t_ast *redir2b = new_redirection(TOKEN_P_DOUBLE_GT, new_command((char*[]){"echo", "Hello append!", NULL}), "append.txt");
    exec_ast(redir2b, &temp_vars, &my_envp);
    free_ast(redir2b);

    printf("Contents of append.txt:\n");
    system("cat append.txt");

    /*----------------- REDIRECTION < input.txt -----------------*/
    printf("\n=== TEST: REDIRECTION < input.txt ===\n");
    FILE *f = fopen("input.txt", "w");
    if (f)
    {
        fprintf(f, "Hello from input.txt!\n");
        fclose(f);
    }
    t_ast *cat_cmd = new_command((char*[]){"cat", NULL});
    t_ast *redir_in = new_redirection(TOKEN_P_LT, cat_cmd, "input.txt");
    exec_ast(redir_in, &temp_vars, &my_envp);
    free_ast(redir_in);
    unlink("input.txt");

    /*----------------- AND && -----------------*/
    printf("\n=== TEST: AND && ===\n");
    t_ast *true_cmd = new_command((char*[]){"true", NULL});
    t_ast *echo_run = new_command((char*[]){"echo", "AND executed", NULL});
    t_ast *and_node = new_binary_op(TOKEN_P_AND, true_cmd, echo_run);
    exec_ast(and_node, &temp_vars, &my_envp);
    free_ast(and_node);

    /*----------------- BUILTINS -----------------*/
    printf("\n=== TEST: BUILTINS ===\n");

    t_ast *env_node = new_command((char*[]){"env", NULL});
    exec_ast(env_node, &temp_vars, &my_envp);
    free_ast(env_node);

    t_ast *cd_node = new_command((char*[]){"cd", "/", NULL});
    exec_ast(cd_node, &temp_vars, &my_envp);
    free_ast(cd_node);

    t_ast *pwd_node = new_command((char*[]){"pwd", NULL});
    exec_ast(pwd_node, &temp_vars, &my_envp);
    free_ast(pwd_node);

    t_ast *echo_builtin = new_command((char*[]){"echo", "hello builtin", NULL});
    exec_ast(echo_builtin, &temp_vars, &my_envp);
    free_ast(echo_builtin);

    t_ast *export_node = new_assignment("BAR=123");
    exec_ast(export_node, &temp_vars, &my_envp);
    export_assignment("BAR=123", &my_envp);
    free_ast(export_node);

    t_ast *unset_node = new_command((char*[]){"unset", "BAR", NULL});
    exec_ast(unset_node, &temp_vars, &my_envp);
    free_ast(unset_node);

    /*----------------- CLEANUP -----------------*/
    free_envp(my_envp);
    return 0;
}
