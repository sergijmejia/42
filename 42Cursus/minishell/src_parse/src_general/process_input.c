/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:56:38 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/28 10:10:20 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_input(char **env, t_list **p_tmp, char *line, t_ast ***ast)
{
	t_list	**lst;

	lst = lexer(line, env, p_tmp);
	if (!lst)
	{
		free(line);
		return (1);
	}
	lst = transition(lst, env, p_tmp, &line);
	if (!lst)
	{
		free(line);
		return (1);
	}
	add_history(line);
	free(line);
	*ast = parser(lst);
	clean_tr(lst);
	if (!(*ast))
		return (1);
	return (0);
}
