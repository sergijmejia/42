/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:00:00 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 16:02:40 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h" // t_temp_lst_exec
#include "minishell.h"      // parser
#include "libft.h"
#include "exec.h"           // prototipo de exec_ast
#include "env.h"
#include "utils.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "global.h"

static int	main_loop(char ***env, t_list **p_tmp, t_temp_lst_exec **tmp)
{
	char	*aux_line;
	char	*line;
	t_ast	*ast;

	aux_line = readline("minishell$ ");
	if (!aux_line)
	{
		printf("exit\n");
		return (0);
	}
	line = ft_strjoin(aux_line, "\n");
	free(aux_line);
	if (!line)
		return (0);
	if (check_parentheses_balance(line) || check_quote_balance(line))
		return (free(line), 1);
	ast = NULL;
	if (process_input(*env, p_tmp, line, &ast))
		return (1);
	exec_ast(ast, tmp, env, p_tmp);
	clean_ast(ast);
	if (g_exit_status == -2)
		return (0);
	return (1);
}

/**
 * @brief Signal handler for Ctrl-C (SIGINT).
 *
 * This handler is triggered when the user presses Ctrl-C.
 * It clears the current input line, moves to a new line,
 * redisplays the prompt, and sets the global exit status to 1.
 *
 * @param signum The signal number (unused).
 */
void	sigint_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
	g_exit_status = 1;
}

/*Convierte la lista del parser (t_list **tmp_var) a tu lista 
enlazada del executor*/
t_temp_lst_exec	*convert_tmp_var(t_list **parser_tmp_var)
{
	t_temp_lst_exec	*head;
	t_temp_lst_exec	*node;
	t_list			*cur;

	head = NULL;
	cur = *parser_tmp_var;
	while (cur)
	{
		node = malloc(sizeof(t_temp_lst_exec));
		if (!node)
			exit(EXIT_FAILURE);
		node->name = ft_strdup(((t_temp_lst *)cur->content)->name);
		node->value = ft_strdup(((t_temp_lst *)cur->content)->value);
		node->next = head;
		head = node;
		cur = cur->next;
	}
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	t_list			**parser_tmp_var;
	t_temp_lst_exec	*tmp_var;
	char			**env;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	parser_tmp_var = create_var_table();
	tmp_var = NULL;
	if (!parser_tmp_var)
		exit(EXIT_FAILURE);
	env = dup_env(envp);
	if (!env)
		exit(EXIT_FAILURE);
	unset_assignment("OLDPWD", &env);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	tmp_var = convert_tmp_var(parser_tmp_var);
	while (main_loop(&env, parser_tmp_var, &tmp_var))
		;
	free_tmp_var_exec(tmp_var);
	ft_lstclear(parser_tmp_var, free_tmp_var_p);
	free(parser_tmp_var);
	free_str(env);
	return (0);
}
