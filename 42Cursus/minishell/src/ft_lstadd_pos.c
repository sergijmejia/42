/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:52:40 by smejia-a          #+#    #+#             */
/*   Updated: 2025/07/05 14:00:41 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que agrega a la lista lst, el nodo new, siendo el next del nodo i*/
void	ft_lstadd_pos(t_list **lst, t_list *new, int i)
{
	t_list	*aux;
	int		len;

	if ((lst == NULL) || (new == NULL))
		return ;
	len = ft_lstsize(*lst);
	if (i >= len)
		return ;
	else
	{
		aux = ft_lstpos(*lst, i);
		new->next = aux->next;
		aux->next = new;
	}
}
