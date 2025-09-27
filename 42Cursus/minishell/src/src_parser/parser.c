/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:32:23 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/26 12:41:42 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que calcula la cantidad de strings que hay en un string doble*/
static int	calculate_strlen(t_token_ast *token)
{
	int		len;
	char	**str;

	if (token == NULL)
		return (-1);
	str = token->value;
	len = 0;
	while (str[len])
		len++;
	return (len);
}

/*Funcion que genera el ast que sera utilizado por el executor*/
t_ast	**parser(t_list **token_list)
{
	int		pos;
	int		size;
	t_ast	**ast_list;

	size = ft_lstsize(*token_list);
	pos = find_and(token_list);
	if (pos < size)
	{
		
	}
}
