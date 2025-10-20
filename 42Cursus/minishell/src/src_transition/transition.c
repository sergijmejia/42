/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:35:53 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 16:00:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona la transicion entre lexer y parser*/
t_list	**transition(t_list **lst, char **env, t_list **tmp_var, char **line)
{
	t_aux	*aux;

	lst = transition_lex_par(lst);
	if (!lst)
		return (NULL);
	if (command_union(lst) == NULL)
		return (NULL);
	aux = (t_aux *) malloc (sizeof(t_aux));
	if (!aux)
		return (error_tr(lst));
	aux->token_list = lst;
	aux->tmp_var = tmp_var;
	aux->env = env;
	aux->x = 0;
	lst = syntax_and_heredoc(aux, line);
	if (!lst)
		return (NULL);
	return (lst);
}
