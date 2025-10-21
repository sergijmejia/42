/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_divider.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:07:41 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 11:09:55 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que encuentra el siguiente '='*/
static int	find_next_equal(char *str, int pos)
{
	while (str[pos])
	{
		if (str[pos] == '=')
			return (pos);
		if (str[pos] == '\'' || str[pos] == '\"')
			pos = next_quote(str, pos);
		pos++;
	}
	return (-1);
}

/*Funcio que encuentra todos los TOKEN_ASSIGNMENT_CANDIDATE*/
static t_list	**divide_assignment(t_list **token_list, int *i)
{
	int		pos;
	int		assignment;
	char	*str;
	t_list	*lst;

	lst = ft_lstpos(*token_list, *i);
	if (!lst)
		return (NULL);
	str = ((t_token *)(lst->content))->value;
	pos = find_next_equal(str, 0);
	while (pos > 0)
	{
		assignment = assignment_candidate(token_list, i, pos);
		if (assignment == -1)
			return (error_list(token_list));
		else if (assignment == 1)
		{
			lst = ft_lstpos(*token_list, *i);
			str = ((t_token *)(lst->content))->value;
			pos = find_next_equal(str, 0);
		}
		else
			break ;
	}
	return (token_list);
}

/*Funcion que divide cada uno de los TOKEN_WORD por espacios*/
t_list	**assignment_divider(t_list **token_list)
{
	int		len;
	int		i;
	t_list	*token_list_aux;

	len = ft_lstsize(*token_list);
	i = 0;
	while (i < len)
	{
		token_list_aux = ft_lstpos(*token_list, i);
		if (!token_list_aux)
			return (error_list(token_list));
		if (((t_token *)(token_list_aux->content))->type == TOKEN_WORD)
		{
			if (divide_assignment(token_list, &i) == NULL)
				return (error_list(token_list));
		}
		i++;
		len = ft_lstsize(*token_list);
	}
	return (token_list);
}
