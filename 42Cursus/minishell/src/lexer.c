/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:49 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/12 11:43:10 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Crea lexer. Pasa todos los argumentos de los string a una lista*/
t_list	**lexer(char *str)
{
	t_list	**lst;

	lst = (t_list **) malloc (sizeof(t_list *));
	if (!lst)
		return (NULL);
	*lst = NULL;
	if (assignment_divider(lst, str) == NULL)
	{
		free(lst);
		return (NULL);
	}
	printf("\nA la salida de assignment:\n");
	print_lst(*lst);
	printf("\n");
	/*if (quote_divider(lst) == NULL)
		return (NULL);
	printf("\nA la salida de quote:\n");
	print_lst(*lst);
	printf("\n");*/
	if (space_divider(lst) == NULL)
	{
		free(lst);
		return (NULL);
	}
	printf("\nA la salida de space:\n");
	print_lst(*lst);
	printf("\n");
	if (special_char_divider(lst) == NULL)
	{
		free(lst);
		return (NULL);
	}
	printf("\nA la salida de special char:\n");
	print_lst(*lst);
	printf("\n");
	if (find_command_option(lst) == NULL)
	{
		free(lst);
		return (NULL);
	}
	printf("\nA la salida de command option:\n");
	print_lst(*lst);
	printf("\n");
	if (variable_expansion(lst) == NULL)
	{
		free(lst);
		return (NULL);
	}
	printf("\nA la salida de variable expansion:\n");
	print_lst(*lst);
	printf("\n");
	if (delete_quotes(lst) == NULL)
	{
		free(lst);
		return (NULL);
	}
	printf("\nA la salida de delete quotes:\n");
	print_lst(*lst);
	printf("\n");
	return (lst);
}
