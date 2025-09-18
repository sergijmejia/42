/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:27:05 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/15 13:38:59 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wildcard(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	} 
	return (0);
}

t_list	**find_wildcard(t_list **token_list)
{
	t_list	*token;
	int		len;
	int		i;
	char	*str;

	len = ft_lstsize(*token_list);
	i = 0;
	while (i < len)
	{
		token = ft_lstpos(*token_list, i);
		if (token == NULL)
			return (token_list);
		if (((t_token *)(token->content))->type == TOKEN_WORD)
		{
			str = ((t_token *)(token->content))->value;
			if (!str)
				return (NULL);
			if (wildcard(str) && ((t_token *)(token->content))->finished == 0)
				((t_token *)(token->content))->type = TOKEN_WILDCARD;
		}
		i++;
	}
	return (token_list); 
}
