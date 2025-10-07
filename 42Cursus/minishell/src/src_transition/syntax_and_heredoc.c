/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:10:02 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/07 13:08:58 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_pipe_and_or(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (1);
	type = ((t_token_ast *) ((ft_lstpos(*token_list, pos - 1))->content))->type;
	if ((type >= 1 && type <= 5) || (type >= 7 && type <= 9))
		return (1);
	else
		return (0);
}

static int	syntax_redirection(t_list **token_list, int pos)
{
	int			size;

	size = ft_lstsize(*token_list);
	if (pos == size - 1)
		return (0);//<----------NO ESTA HACIENDO NADA... SE PUEDE ELIMINAR LA FUNCION
	return (0);
}

static int	syntax_assignment_lparenthesis(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (0);
	type = ((t_token_ast *) ((ft_lstpos(*token_list, pos - 1))->content))->type;
	if (type == 1 || type == 7 || type == 8)
		return (0);
	else
		return (1);
}

static int	syntax_rparenthesis(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (1);
	type = ((t_token_ast *) ((ft_lstpos(*token_list, pos - 1))->content))->type;
	if ((type >= 1 && type <= 5) || type == 7 || type == 8)
		return (0);
	else
		return (1);
}

static int	syntax_name(t_list **token_list, int pos, char **line)
{
	t_type_tr	type;


	printf("Entra en el syntax_name con pos=%d\n", pos);
	if (pos == 0)
	{
		printf("Fallo en opcion 1\n");
		return (1);
	}
	type = ((t_token_ast *) ((ft_lstpos(*token_list, pos - 1))->content))->type;
	if (type < 2 || type > 5)
	{
		printf("Fallo en opcion 2\n"); 
        return (1);
	}
	if (type == 5)
	{
		if (heredoc(token_list, pos, line))
		{
			printf("Fallo en opcion 3\n"); 
			return (1);
		}
	}
	return (0);
}

static int	syntax_newline(t_list **token_list, int pos)
{
	t_type_tr	type;

	if (pos == 0)
		return (0);
	type = ((t_token_ast *) ((ft_lstpos(*token_list, pos - 1))->content))->type;
	if ((type >= 1 && type <= 5) || (type >= 7 && type <= 9))
		return (1);
	else
		return (0);
}

t_list	**syntax_and_heredoc(t_list **lst, char **line)
{
	int			x[2];
	t_type_tr	type;
	int			syntax;

	x[0] = 0;
	x[1] = ft_lstsize(*lst);
	syntax = 0;
	while (x[0] < x[1])
	{
		type = ((t_token_ast *) ((ft_lstpos(*lst, x[0]))->content))->type;
		if (type == 1 || type == 7 || type == 8)
			syntax = syntax_pipe_and_or(lst, x[0]);
		else if (type >= 2 && type <= 5)
			syntax = syntax_redirection(lst, x[0]);
		else if (type == 6 || type == 9)
			syntax = syntax_assignment_lparenthesis(lst, x[0]);
		else if (type == 10)
			syntax = syntax_rparenthesis(lst, x[0]);
		else if (type == 11)
			syntax = syntax_name(lst, x[0], line);
		if (syntax == 1)
			return (error_syntax(lst, x[0]));
		x[0]++;
	}
	if (syntax_newline(lst, x[1]))
		return (error_syntax(lst, x[1]));
	return (lst);

	/*check_parentheses_balance(line);
	 * */

}
