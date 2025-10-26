/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:52:40 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/05 08:36:20 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Funcion que agrega a la lista lst, el nodo new, en la posicion i*/
void	ft_lstadd_pos(t_list **lst, t_list *new, int i)
{
	t_list	*front;
	t_list	*back;
	int		len;

	if ((lst == NULL) || (new == NULL))
		return ;
	len = ft_lstsize(*lst);
	if (i < 0)
		return ;
	if (i == 0)
		ft_lstadd_front(lst, new);
	else if (i < len)
	{
		front = ft_lstpos(*lst, i - 1);
		back = ft_lstpos(*lst, i);
		new->next = back;
		front->next = new;
	}
	else if (i == len)
		ft_lstadd_back(lst, new);
	else
		return ;
}
