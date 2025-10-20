/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:45:23 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 15:09:14 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que elimina e ultimo elemento de una lista*/
void	ft_lstdel_last(t_list **lst, void (*del)(void*))
{
	t_list	*second_last;
	t_list	*last;
	int		len;

	if (!lst || !del)
		return ;
	len = ft_lstsize(*lst);
	if (len > 1)
		second_last = ft_lstsecondlast(*lst);
	last = ft_lstlast(*lst);
	ft_lstdelone(last, del);
	if (len > 1)
		second_last->next = NULL;
	else
		*lst = NULL;
	return ;
}
