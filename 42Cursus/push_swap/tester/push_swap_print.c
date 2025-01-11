/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:04:25 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/09 13:59:29 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ***********************  FUNCIONES IMPRIMIR LISTA  *********************** */
/*Estas funciones son para testear. En cas de querer utilizarlas se han de 
agregar al Makefile y al header*/

/*Imprime por pantalla la lista lst*/
void	print_lst(t_list *lst)
{
	if (lst == NULL)
		return ;
	ft_printf("%d ", *(int *)(lst->content));
	if (lst->next != NULL)
	{
		print_lst(lst->next);
		return ;
	}
}

/*Imprime por pantalla las dos listas a y b*/
void	print_ab_lists(t_list *a, t_list *b)
{
	ft_printf("Lista a: ");
	print_lst(a);
	ft_printf("\nLista b: ");
	print_lst(b);
	ft_printf("\n");
}
