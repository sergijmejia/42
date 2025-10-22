/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:16:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/25 16:36:15 by smejia-a         ###   ########.fr       */
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
	while (i < size)
	{
		token = (t_token *)((ft_lstpos(*token_list, i))->content);
		if (token == NULL)
			return (error_list(token_list));
		type = token->type;
        if (i != size - 1)
        {
            token = (t_token *)((ft_lstpos(*token_list, i + 1))->content);
                if (token == NULL)
	    			return (error_list(token_list));
    		if (type >= 5 && type <= 7)
    		{	    		
	    		type = token->type;
	    		if (type == 0 || type == 2 || type == 3 || type == 9)
	    			token->type = TOKEN_REDIRECTION_WORD;
            }
            else if (type == 8)
            {
                type = token->type;
                if (type == 0 || type == 2 || type == 3 || type == 9)
                    token->type = TOKEN_REDIRECTION_HEREDOC;
            }
		}
		i++;
	}
	return (token_list);
}
