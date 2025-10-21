/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_divider.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:27:55 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/13 13:06:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que define los special char*/
static void	define_special(char *special_char)
{
	special_char[0] = '<';
	special_char[1] = '>';
	special_char[2] = '|';
	special_char[3] = '&';
	special_char[4] = ')';
	special_char[5] = '(';
	special_char[6] = 0;
	return ;
}

/*Funcion para buscar los caracteres especiales en todos los TOKEN_WORD*/
t_list	**special_char_divider(t_list **token_list)
{
	int		len;
	int		i;
	t_list	*token_list_aux;
	t_token	*token;
	char	special_char[7];

	len = ft_lstsize(*token_list);
	define_special(&special_char[0]);
	i = 0;
	while (i < len)
	{
		token_list_aux = ft_lstpos(*token_list, i);
		token = (t_token *)(token_list_aux->content);
		if (!token_list_aux)
			return (error_list(token_list));
		if (token->finished == 0)
		{
			if (token->type == 0 || token->type == 2 || token->type == 3)
				if (divide_special(token_list, &i, &special_char[0]) == NULL)
					return (error_list(token_list));
		}
		i++;
		len = ft_lstsize(*token_list);
	}
	return (token_list);
}
