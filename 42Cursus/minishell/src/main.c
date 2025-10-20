/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:48:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 16:01:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

/*Este es un programa para ir testeand tods los componentes*/
int	main(int argc, char **argv, char **envp)
{
	t_list	**tmp_var;
	t_list	**lst;
	t_ast	**ast;
	char	*line;
	char	**env;

	if (argc != 1)
	{
		ft_printf("Entra en el condicional\nError por: %s\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	g_exit_status = 0;
	tmp_var = create_var_table();
	if (tmp_var == NULL)
	{
		ft_printf("Error en la creacion de tabla\n");
		exit(EXIT_FAILURE);
	}
	env = dup_env(envp);
	//while (1)
	//{
		//line = readline("minishell$ ");
		ft_printf("minishell$ ");
		line = get_next_line(0);
		if (!line)
			exit(EXIT_FAILURE);
		//else
			//add_history(line);
		if (check_parentheses_balance(line)) //esto en realidad se deberia checkear en el syntax
											 //para eso hay que modificar el parentheses_divider 
											 //en el lexer para simpllemente crear los nodos de
											 //parentesis abierto/cerrado 
		{
			printf("Error: parentheses not balanced\n");
			free (line);
		}
		else if (check_quote_balance(line))
		{
			printf("Error\n");
			free (line);
		}
		else
		{
			lst = lexer(line, env, tmp_var);
			//free(line);
			if (!lst)
			{
				free(line);
				//rl_clear_history();
				exit(EXIT_FAILURE);
			}
			printf("\nA la salida de lexer:\n");
			printf("\n");
			print_lst(*lst);
			printf("\n");
			/*lst = transition_lex_par(lst);
			if (!lst)
			{
				free(line);
				//rl_clear_history();
				exit(EXIT_FAILURE);
			}
			printf("\nA la salida de tansition:\n");
            printf("\n");
			print_lst_tr(*lst);
            printf("\n");
			if (command_union(lst) == NULL)
			{
				free(line);
				//rl_clear_history();
				exit(EXIT_FAILURE);
			}
			printf("\nA la salida de union:\n");
			printf("\n");
			print_lst_tr(*lst);
			printf("\n");
			lst = syntax_and_heredoc(lst, &line, env, tmp_var);
			if (!lst)
			{
				free(line);
				//rl_clear_history();
				exit(EXIT_FAILURE);
			}
			printf("\nA la salida de syntax:\n");
            printf("\n");
            print_lst_tr(*lst);
            printf("\n");*/
			lst = transition(lst, env, tmp_var, &line);
			if (!lst)
			{
				free(line);
				exit(EXIT_FAILURE);
			}
			printf("\nA la salida de transition:\n");
			printf("\n");
			print_lst_tr(*lst);
			printf("\n");
			printf("El line modificado es:\n");
			printf("%s", line);
			printf("\n");
			//add_history(line);
			free(line);
			ast = parser(lst);
			if (!ast)
			{
				error_tr(lst);
				//rl_clear_history();
				exit(EXIT_FAILURE);
			}
			printf("\nA la salida del parser:\n");
            printf("\n");
            print_ast(*ast);
            printf("\n");


			error_ast(ast);
			error_tr(lst);
			free_str(env);

			//execute_ast(*ast, temp_var, &env) ast debe ser puntero simple (t_ast *), temp_var es la tabla de variables (char **), envp es el enviroment (char ***) <--- PUNTERO TRIPLE!!!!


			//free(lst);
		}
	//}
	//rl_clear_history();
	//free(((t_temp_lst *)((*tmp_var)->content))->name);
	//free(((t_temp_lst *)((*tmp_var)->content))->value);
	//free((t_temp_lst *)((*tmp_var)->content));
	//free(*tmp_var);
	free(tmp_var);
	exit(EXIT_SUCCESS);
}
