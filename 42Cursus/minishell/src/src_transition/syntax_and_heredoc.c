/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:10:02 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/17 13:49:04 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica la sintaxis de pipe, and y or*/
static int	syntax_pipe_and_or(t_list **token_list, int pos)
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

/*Funcion que verifica la sintaxis de asignaciones y parentesis izquierdo*/
static int	syntax_assignment_lparenthesis(t_list **token_list, int pos)
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

/*Funcion que verifica la sintaxis de name*/
static int	syntax_name(t_list **token_list, int pos, char **line)
{
	t_type_tr	type;

	if (pos == 0)
		return (1);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos - 1))->content))->type;
	if (type < 2 || type > 5)
		return (1);
	if (type == 5)
	{
		if (heredoc(token_list, pos, line))
			return (1);
	}
	return (0);
}

/*Funcion que verifica la sintaxis de newline*/
static int	syntax_newline(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (0);
	type = ((t_token_ast *)((ft_lstpos(*token_list, pos - 1))->content))->type;
	printf("\nEl type es: %d\n", type);
	if ((type >= 1 && type <= 5) || (type >= 7 && type <= 9))
		return (1);
	else
		return (0);
}

/*Funcion que gestiona el loop del syntax_and_heredoc*/
static int	syntax_and_heredoc_loop(t_list **lst, char **line, int i)
{
	int			syntax;
	t_type_tr	type;

	syntax = 0;
	type = ((t_token_ast *)((ft_lstpos(*lst, i))->content))->type;
	if (type == 1 || type == 7 || type == 8)
		syntax = syntax_pipe_and_or(lst, i);
	else if (type >= 2 && type <= 5)
		syntax = syntax_redirection(lst, i);
	else if (type == 6 || type == 9)
		syntax = syntax_assignment_lparenthesis(lst, i);
	else if (type == 10)
		syntax = syntax_rparenthesis(lst, i);
	else if (type == 11)
		syntax = syntax_name(lst, i, line);
	return (syntax);
}

/*Funcion que gestiona el heredoc y los errores de sintaxis*/
t_list	**syntax_and_heredoc(t_list **lst, char **line)
{
	int			i;
	int			size;
	int			syntax;

	i = 0;
	size = ft_lstsize(*lst);
	while (i < size)
	{
		syntax = syntax_and_heredoc_loop(lst, line, i);
		if (syntax == 1)
			return (error_syntax(lst, i));
		i++;
	}
	if (syntax_newline(lst, size))
		return (error_syntax(lst, size));
	return (lst);
}
