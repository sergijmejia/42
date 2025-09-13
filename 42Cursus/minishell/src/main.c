/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:48:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/12 11:53:25 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

/*Este es un programa para ir testeand tods los componentes*/
int	main(void)
{
	t_list	**lst;
	char	*line;

	g_exit_status = 0;
	//while (1)
	//{
		//line = readline("minishell$ ");
		ft_printf("minishell$ ");
		line = get_next_line(0);
		printf("\n\n%s\n\n", line);
		if (!line)
			exit(EXIT_FAILURE);
		//else
			//add_history(line);
		if (check_parentheses_balance(line))
		{
			printf("Error\n");
			free (line);
		}
		else if (check_quote_balance(line))
		{
			printf("Error\n");
			free (line);
		}
		else
		{
			lst = lexer(line);
			free(line);
			if (!lst)
			{
				//rl_clear_history();
				exit(EXIT_FAILURE);
			}
			print_lst(*lst);
			ft_lstclear(lst, delete_token);
			free(lst);
		}
	//}
	//rl_clear_history();
	exit(EXIT_SUCCESS);
}
