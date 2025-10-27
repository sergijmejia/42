/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:41:14 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/18 00:33:36 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "builtins.h"
#include "libft.h"
#include "minishell_exec.h"
#include <stdlib.h>

extern int g_exit_status;

/* Libera la lista enlazada del executor */
static void free_tmp_var(t_temp_lst_exec *lst)
{
    t_temp_lst_exec *tmp;

    while (lst)
    {
        tmp = lst->next;
        free(lst->name);
        free(lst->value);
        free(lst);
        lst = tmp;
    }
}

/* Libera la lista de variables del parser */
static void free_parser_tmp_var(t_list **lst)
{
    t_list *tmp;
    t_list *current;

    if (!lst || !*lst)
        return;

    current = *lst;
    while (current)
    {
        tmp = current->next;
        free(current->content);  // asumimos que content apunta al string duplicado
        free(current);
        current = tmp;
    }
    *lst = NULL;
}

/* Libera el array de strings del entorno */

static void free_envp(char **env)
{
    int i;

    if (!env)
        return;

    for (i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}


/* Limpieza completa de la shell antes de exit */
static void cleanup_shell(t_temp_lst_exec *tmp_var, t_list **parser_tmp_var, char **env)
{
    if (tmp_var)
        free_tmp_var(tmp_var);

    if (parser_tmp_var)
        free_parser_tmp_var(parser_tmp_var);

    if (env)
        free_envp(env);
}

/**
 * @brief Builtin exit que limpia la shell antes de salir.
 *
 * @param args Argumentos del comando, args[1] puede contener el código de salida
 * @param tmp_var Lista temporal de variables del executor
 * @param parser_tmp_var Tabla de variables del parser
 * @param env Entorno de la shell
 */
int 	builtin_exit(char **args, t_temp_lst_exec *tmp_var, char **env, t_list **parser_tmp_var)
{
    int code;

    if (!args || !args[1])
        code = g_exit_status;
    else
        code = ft_atoi(args[1]);

    cleanup_shell(tmp_var, parser_tmp_var, env);

    exit(code);
}
