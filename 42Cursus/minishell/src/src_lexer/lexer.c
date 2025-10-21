/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:49 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 10:47:08 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Crea lexer. Pasa todos los argumentos de los string a una lista*/
t_list	**lexer(char *str, char **env, t_list **tmp_var)
{
	t_list	**lst;

	lst = (t_list **) malloc (sizeof(t_list *));
	if (!lst)
		return (NULL);
	*lst = NULL;
	if (paren_divider(lst, str, env, tmp_var) == NULL)
		return (NULL);
	if (assignment_divider(lst) == NULL)
		return (NULL);
	if (space_divider(lst) == NULL)
		return (NULL);
	if (special_char_divider(lst) == NULL)
		return (NULL);
	if (find_redirection(lst) == NULL)
		return (NULL);
	if (find_wildcard(lst) == NULL)
		return (NULL);
	if (var_expansion(lst, env, tmp_var) == NULL)
		return (NULL);
	if (delete_quotes(lst) == NULL)
		return (NULL);
	if (assignment_selection(lst) == NULL)
		return (NULL);
	return (lst);
}
