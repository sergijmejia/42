/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:49 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/29 16:05:05 by smejia-a         ###   ########.fr       */
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
	/*printf("1- La lst es:\n");
	print_lst(*lst);
	printf("\n");*/
	if (assignment_divider(lst) == NULL)
		return (NULL);
	/*printf("2- La lst es:\n");
    print_lst(*lst);
    printf("\n");*/
	if (space_divider(lst) == NULL)
		return (NULL);
	/*printf("3- La lst es:\n");
    print_lst(*lst);
    printf("\n");*/
	if (special_char_divider(lst) == NULL)
		return (NULL);
	/*printf("4- La lst es:\n");
    print_lst(*lst);
    printf("\n");*/
	if (find_redirection(lst) == NULL)
		return (NULL);
	/*printf("5- La lst es:\n");
    print_lst(*lst);
    printf("\n");*/
	if (find_wildcard(lst) == NULL)
		return (NULL);
	/*printf("6- La lst es:\n");
    print_lst(*lst);
    printf("\n");*/
	if (variable_expansion(lst) == NULL)
		return (NULL);
	/*printf("7- La lst es:\n");
    print_lst(*lst);
    printf("\n");*/
	if (delete_quotes(lst) == NULL)
		return (NULL);
	/*printf("8- La lst es:\n");
    print_lst(*lst);
    printf("\n");*/
	if (assignment_selection(lst) == NULL)
		return (NULL);
	/*write(1, "9- La lst es:\n", 14);
    print_lst(*lst);
    printf("\n");*/
	return (lst);
}
