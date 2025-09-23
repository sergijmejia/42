/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:16:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/22 10:28:00 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**find_redirection(t_list **token_list)
{
	int				size;
	int				i;
	t_token			*token;
	t_type_lexer	type;

	size = ft_lstsize(*token_list);
	i = 0;
	printf("Entra en el redirection\n");
	while (i < size)
	{
		token = (t_token *)((ft_lstpos(*token_list, i))->content);
		if (token == NULL)
			return (error_list(token_list));
		printf("\nAnaliza %s\n", token->value);
		type = token->type;
		if ((type >= 5 && type <= 8) && i != size - 1)
		{
			token = (t_token *)((ft_lstpos(*token_list, i + 1))->content);
			if (token == NULL)
				return (error_list(token_list));
			type = token->type;
			if (type == 0 || type == 2 || type == 3 || type == 9)
			{
				printf("\nTransforma %s\n", token->value);
				token->type = TOKEN_REDIRECTION_WORD;
			}
		}
		i++;
	}
	return (token_list);
}
