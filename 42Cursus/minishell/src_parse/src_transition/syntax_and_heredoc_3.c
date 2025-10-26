/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_heredoc_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:56:43 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 13:57:32 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica la sintaxis de and y or*/
static int	syntax_and_or(t_list **token_list, int pos)
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

/*Funcion que verifica la sintaxis de parentesis izquierdo*/
static int	syntax_lparenthesis(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (0);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos - 1))->content))->type;
	if (type == 1 || type == 7 || type == 8)
		return (0);
	else
		return (1);
}

/*Funcion que verifica la sintaxis de parentesis derecho*/
static int	syntax_rparenthesis(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (1);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos - 1))->content))->type;
	if ((type >= 1 && type <= 5) || type == 7 || type == 8)
		return (1);
	else
		return (0);
}

/*Funcion que verifica la syntaxis de los type del bonus del minishell*/
int	syntax_bonus(t_list **lst, int pos, int type)
{
	int	syntax;

	syntax = 0;
	if (type == 7 || type == 8)
		syntax = syntax_and_or(lst, pos);
	else if (type == 9)
		syntax = syntax_lparenthesis(lst, pos);
	else if (type == 10)
		syntax = syntax_rparenthesis(lst, pos);
	return (syntax);
}
