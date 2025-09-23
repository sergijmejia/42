/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:49 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/22 13:12:37 by smejia-a         ###   ########.fr       */
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
	if (parentheses_divider(lst, str) == NULL)
		return (NULL);
	printf("A la salida de parentesis:\n");
	print_lst(*lst);
	printf("\n");
	if (assignment_divider(lst) == NULL)
		return (NULL);
	printf("A la salida de assigment:\n");
	print_lst(*lst);
	printf("\n");
	if (space_divider(lst) == NULL)
		return (NULL);
	printf("A la salida de space:\n");
	print_lst(*lst);
	printf("\n");
	if (special_char_divider(lst) == NULL)
		return (NULL);
	printf("A la salida de char:\n");
	print_lst(*lst);
	printf("\n");
	if (find_redirection(lst) == NULL)
		return (NULL);
	printf("A la salida de redirection:\n");
	print_lst(*lst);
	printf("\n");
	/*if (find_command_option(lst) == NULL)  <------ NO TIENE NINGUNA RELEVANCIA
		return (NULL);
	printf("A la salida de comand option:\n");
	print_lst(*lst);
	printf("\n");*/
	if (find_wildcard(lst) == NULL)
		return (NULL);
	if (variable_expansion(lst) == NULL)
		return (NULL);
	if (delete_quotes(lst) == NULL)
		return (NULL);
	return (lst);
}
