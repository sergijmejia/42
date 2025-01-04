/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:27:32 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/23 13:00:03 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* *****************  FUNCIONES DE MOVIMIENTO DE PUSH_SWAP  ***************** */

/*Intercambia las dos primeras posiciones de la lista lst*/
void	swap(t_list **lst)
{
	t_list	*aux;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	aux = (*lst)->next;
	(*lst)->next = aux->next;
	aux->next = *lst;
	*lst = aux;
	return ;
}

/*Intercambia las dos primeras posiciones en la lista lst_a y en la lista lst_b
a la vez*/
void	swap_swap(t_list **lst_a, t_list **lst_b)
{
	swap(lst_a);
	swap(lst_b);
	return ;
}

/*Toma el primer elemento de la lista lst_b y lo pone el primero en la lista 
lst_a*/
void	push(t_list **lst_a, t_list **lst_b)
{
	t_list	*aux;

	if (*lst_b == NULL)
		return ;
	aux = (*lst_b)->next;
	(*lst_b)->next = (*lst_a);
	*lst_a = *lst_b;
	*lst_b = aux;
	return ;
}

/*Desplaza hacia arriba todos los elementos del la lista lst*/
void	rotate(t_list **lst)
{
	t_list	*aux;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	aux = *lst;
	*lst = (*lst)->next;
	aux->next = NULL;
	ft_lstadd_back(lst, aux);
	return ;
}

/*Desplaza hacia arriba todos los elementos de la lista lst_a y la lista lst_b 
a la vez*/
void	rotate_rotate(t_list **lst_a, t_list **lst_b)
{
	rotate(lst_a);
	rotate(lst_b);
	return ;
}
