/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:14:32 by smejia-a          #+#    #+#             */
/*   Updated: 2025/06/08 14:39:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Imprime por pantalla la lista lst*/
void	print_lst(t_list *lst)
{
	t_token *token;
	if (lst == NULL)
		return ;
	token = (t_token *) (lst->content);
	ft_printf("%s\n", (char *)(token->value));
	if (lst->next != NULL)
	{
		print_lst(lst->next);
		return ;
	}
}
