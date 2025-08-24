/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:49 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/18 18:26:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Crea lexer. Pasa todos los argumentos de los string a una lista*/
t_list	**lexer(char *str)
{
	t_list	**lst;

	*lst = NULL;
	while (*str)
	{
		if (check_parentheses_balance(str))
		{
			printf("Error\n");
			return (EXIT_FAILURE);
		}
		quote_divider(lst, str);
		free(str);
		space_divider(lst);
		special_char_divider(lst);
		find_command_option(lst);
	}
	variable_expansion(lst);
	return (lst);
}
