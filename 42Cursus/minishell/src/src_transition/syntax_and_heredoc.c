/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:10:02 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 17:39:09 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica la sintaxis de newline*/
static int	syntax_newline(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (0);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos - 1))->content))->type;
	if ((type >= 1 && type <= 5) || (type >= 7 && type <= 9))
		return (1);
	else
		return (0);
}

/*Funcion que gestiona el loop del syntax_and_heredoc*/
static int	syntax_and_heredoc_loop(t_aux *aux, char **line, int i)
{
	int			syntax;
	t_type_tr	type;
	t_list		**lst;

	lst = aux->token_list;
	syntax = 0;
	type = ((t_token_ast *)((ft_lstpos(*lst, i))->content))->type;
	if (type >= 7 && type <= 10)
		syntax = syntax_bonus(lst, i, type);
	else
		syntax = syntax_mandatory(aux, i, line);
	return (syntax);
}

/*Funcion que gestiona el heredoc y los errores de sintaxis*/
t_list	**syntax_and_heredoc(t_aux *aux, char **line)
{
	int			i;
	int			size;
	int			syntax;
	t_list		**lst;

	i = 0;
	lst = aux->token_list;
	size = ft_lstsize(*lst);
	while (i < size)
	{
		syntax = syntax_and_heredoc_loop(aux, line, i);
		if (syntax == 1)
			return (error_syntax(lst, i));
		i++;
	}
	if (syntax_newline(lst, size))
		return (error_syntax(lst, size));
	return (lst);
}
