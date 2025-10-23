/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_heredoc_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:26:50 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 13:51:50 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica la sintaxis de pipe*/
static int	syntax_pipe(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (1);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos - 1))->content))->type;
	if ((type >= 1 && type <= 5) || (type >= 7 && type <= 9))
		return (1);
	else
		return (0);
}

/*Funcion que verifica la sintaxis de redirecciones*/
static int	syntax_redirection(t_list **token_list, int pos)
{
	int			size;

	size = ft_lstsize(*token_list);
	if (pos == size - 1)
		return (0);
	return (0);
}

/*Funcion que verifica la sintaxis de asignaciones*/
static int	syntax_assignment(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (0);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos - 1))->content))->type;
	if (type == 1 || type == 6 || type == 7 || type == 8 || type == 9)
		return (0);
	else
		return (1);
}

/*Funcion que verifica la sintaxis de name*/
static int	syntax_name(t_aux *aux, int pos, char **line)
{
	t_type_tr	type;
	t_list		**token_list;

	token_list = aux->token_list;
	if (pos == 0)
		return (1);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos - 1))->content))->type;
	if (type < 2 || type > 5)
		return (1);
	if (type == 5)
	{
		if (heredoc(aux, pos, line))
			return (1);
	}
	return (0);
}

/*Funcion que verifica la syntaxis de los type del mandatory del minishell*/
int	syntax_mandatory(t_aux *aux, int pos, char **line)
{
	int			syntax;
	t_type_tr	type;
	t_list		**lst;

	lst = aux->token_list;
	syntax = 0;
	type = ((t_token_ast *)((ft_lstpos(*lst, pos))->content))->type;
	if (type == 1)
		syntax = syntax_pipe(lst, pos);
	else if (type >= 2 && type <= 5)
		syntax = syntax_redirection(lst, pos);
	else if (type == 6)
		syntax = syntax_assignment(lst, pos);
	else if (type == 11)
		syntax = syntax_name(aux, pos, line);
	return (syntax);
}
