/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_divider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:55:03 by smejia-a          #+#    #+#             */
/*   Updated: 2025/06/10 18:08:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que divide cada uno de los TOKEN_WORD por comillas*/
void	space_divider(t_list **token_list)
{
	int	len;
	int	i;
	t_list	*token_aux;

	len = lstsize(*token_list);
	i = 0;
	token_aux = *token_list;
	while (i < len)
	{
		if (token_aux->e_tpkrntype == TOKEN_WORD)
			divide_space(token_aux);
		token_aux = token_aux->next;
	}
}
