/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_divider_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:12:30 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 11:23:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica que el caracter c es correcto para el nombre*/
/*Si x = 0 estamos evaluando la primera letra. x = 1 cualquier otra letra*/
static int	correct_name_char(char c, int x)
{
	if (x == 0)
	{
		if (ft_isalpha(c) || c == '_')
			return (1);
		else
			return (0);
	}
	else
	{
		if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
			return (1);
		else
			return (0);
	}
}

/*Funcion que busca el inicio del assignment*/
static int	find_start_assignment(char *str, int pos)
{
	int		i;
	char	space[4];

	space[0] = 9;
	space[1] = 10;
	space[2] = 32;
	space[3] = 0;
	i = pos - 1;
	if (i == -1)
		return (-1);
	while (i >= 0 && correct_name_char(str[i], 1))
		i--;
	if (i == -1)
	{
		if (correct_name_char(str[0], 0))
			return (0);
		return (-1);
	}
	if (ft_strcontains(&space[0], str[i]) && correct_name_char(str[i + 1], 0))
		return (i + 1);
	else
		return (-1);
}

/*Funcion que busca el final del asssignment*/
static int	find_end_assignment(char *str, int pos)
{
	char	spacing_char[4];

	spacing_char[0] = 9;
	spacing_char[1] = 10;
	spacing_char[2] = 32;
	spacing_char[3] = 0;
	while (str[pos])
	{
		if (ft_strcontains(&spacing_char[0], str[pos]))
			return (pos);
		if (str[pos] == '\'' || str[pos] == '\"')
			pos = next_quote(str, pos);
		pos++;
	}
	return (pos);
}

/*Funcion que agrega los nuevos nodos*/
static t_list	**add_nodes(t_list **lst, t_list **new, int *i, int pos[2])
{
	int		len;
	char	*str;

	str = ((t_token *)(ft_lstpos(*lst, *i)->content))->value;
	len = ft_strlen(str);
	ft_lstdel_pos(lst, delete_token, *i);
	if (pos[0] > 0)
	{
		ft_lstadd_pos(lst, new[0], *i);
		(*i)++;
	}
	ft_lstadd_pos(lst, new[1], *i);
	if (len - 1 >= pos[1] + 1)
	{
		(*i)++;
		ft_lstadd_pos(lst, new[2], *i);
	}
	free(new);
	return (lst);
}

/*Funcionn que crea un TOKEN_ASSIGNMENT_CANDIDATE*/
int	assignment_candidate(t_list **lst, int *i, int pos)
{
	int		start_end[2];
	char	*str_token;
	t_token	*token;
	t_list	**new_nodes;

	token = (t_token *)(ft_lstpos(*lst, *i)->content);
	str_token = token->value;
	start_end[0] = find_start_assignment(str_token, pos);
	if (start_end[0] != -1)
	{
		start_end[1] = find_end_assignment(str_token, pos + 1) - 1;
		if (start_end[1] != -1)
		{
			new_nodes = generate_nodes(lst, *i, start_end[0], start_end[1]);
			if (new_nodes == NULL)
				return (-1);
			if (add_nodes(lst, new_nodes, i, start_end) == NULL)
				return (-1);
			else
				return (1);
		}
	}
	return (0);
}
