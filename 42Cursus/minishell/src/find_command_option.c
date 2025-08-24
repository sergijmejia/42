/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_option.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:04:53 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/22 20:06:51 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_command_option(t_list **token_list)
{
	t_list	*token;
	int		len;
	int		i;
	char	*str;

	token = *token_list;
	len = ft_lstsize(*token_list);
	i = 0;
	while (i < len)
	{
		token = ft_lstpos(*token_list, i);
		if (token == NULL)
			return ;
		if (((t_token *)(token->content))->type == TOKEN_WORD)
		{
			str = ((t_token *)(token->content))->value;
			if (!str)
				error_list(token_list);
			if (str[0] == '-')
				((t_token *)(token->content))->type = TOKEN_COMMAND_OPTION;
		}
		i++;
	}

}
