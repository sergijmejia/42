/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:09:37 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/15 11:21:31 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Fucion que elimina de la lista lst el nodo old, en la posicion x*/
void	ft_lstdel_pos(t_list **lst, void (*del)(void*), int x)
{
	int		size;
	t_list	*old;

	size = (int) ft_lstsize(*lst);
	if ((x < 0) || (x >= size))
		return ;
	old = ft_lstpos(*lst, x);
	if (x == 0)
		*lst = old->next;
	if (x > 0)
		ft_lstpos(*lst, x - 1)->next = old->next;
	ft_lstdelone(old, del);
	return ;
}
