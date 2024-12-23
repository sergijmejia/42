/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rules_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:58:25 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/23 12:58:52 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* *****************  FUNCIONES DE MOVIMIENTO DE PUSH_SWAP  ***************** */

/*Desplaza hacia abajo todos los elementos de la lista lst*/
void	reverse_rotate(t_list **lst)
{
	t_list	*aux;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	aux = ft_lstlast(*lst);
	(ft_lstsecondlast(*lst))->next = NULL;
	ft_lstadd_front(lst, aux);
	return ;
}

/*Desplaza hacia abajo todos los elementos de la lista lst_a y la lista lst_b 
a la vez*/
void	reverse_rotate_rotate(t_list **lst_a, t_list **lst_b)
{
	reverse_rotate(lst_a);
	reverse_rotate(lst_b);
	return ;
}
