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

/*Funcion que cuenta la cantidad de nl que hay en line*/
static int	count_nl(char *line)
{
	int	nl;
	int	i;

	i = 0;
	nl = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			nl++;
		i++;
	}
	return (nl);
}

/*Funcion que elmina el ultimo nl*/
static char	*reduce_nl(char *line)
{
	int		len;
	int		i;
	char	*new_line;
	
	len = (int) ft_strlen(line);
	new_line = (char *) malloc (len * sizeof(char));
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (i < (len - 1))
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[len - 1] = '\0';
	return (new_line);
}

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
static int	snh_loop(t_aux *aux, char **line, int i)
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
	int			count_size_syntax[3];
	char		*aux_line;
	t_list		**lst;

	count_size_syntax[0] = 0;
	lst = aux->token_list;
	count_size_syntax[1] = ft_lstsize(*lst);
	while (count_size_syntax[0] < count_size_syntax[1])
	{
		count_size_syntax[2] = snh_loop(aux, line, count_size_syntax[0]);
		if (count_size_syntax[2] == 1)
			return (error_syntax(lst, count_size_syntax[0]));
		count_size_syntax[0]++;
	}
	if (syntax_newline(lst, count_size_syntax[1]))
		return (error_syntax(lst, count_size_syntax[1]));
	if (count_nl(*line) == 1)
	{
		aux_line = reduce_nl(*line);
		if (aux_line== NULL)
			return (error_tr(lst));
		free (*line);
		*line = aux_line;
	}
	return (lst);
}
