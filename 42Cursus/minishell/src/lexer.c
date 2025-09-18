/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:49 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/18 17:09:54 by smejia-a         ###   ########.fr       */
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
	if (assignment_divider(lst) == NULL)
		return (NULL);
	if (space_divider(lst) == NULL)
		return (NULL);
	if (special_char_divider(lst) == NULL)
		return (NULL);
	if (find_command_option(lst) == NULL)
		return (NULL);
	if (find_wildcard(lst) == NULL)
		return (NULL);
	if (variable_expansion(lst) == NULL)
		return (NULL);
	if (delete_quotes(lst) == NULL)
		return (NULL);
	return (lst);
}
