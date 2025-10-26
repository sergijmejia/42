/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:14:32 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 15:07:45 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Imprime por pantalla la lista lst*/
void	print_lst(t_list *lst)
{
	t_token	*token;

	if (lst == NULL)
		return ;
	token = (t_token *)(lst->content);
	ft_printf("%s", (char *)(token->value));
	ft_printf("(%d)", token->type);
	if (token->finished == 1)
		ft_printf(" --finished");
	ft_printf("\n");
	if (lst->next != NULL)
	{
		print_lst(lst->next);
		return ;
	}
}
