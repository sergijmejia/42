/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_organize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:01:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/08 16:15:42 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ***************************  FUNCION ORGANIZE  *************************** */

/*Funcion que realiza el movimiento push o reverse_rotate en base a los valores
recibidos*/
static int	pa_or_rra(t_list *a, int b_first, int a_last)
{
	int	option;
	int	max;
	int	min;
	int	a_first;

	min = ft_lstmin(a);
	max = ft_lstmax(a);
	a_first = *(int *)(a->content);
	option = 0;
	if (b_first < a_last && b_first < a_first && a_last == max)
		option = 1;
	if (b_first > a_last && b_first < a_first)
		option = 1;
	if (b_first > a_last && b_first > a_first && a_first == min)
		option = 1;
	return (option);
}

/*Funcion que devuelve la lista a organizada con el min arriba y en la menor
cantidad de mov posibles*/
static void	organize_a(t_list **a, t_list **b, int size_b)
{
	int	b_first;
	int	a_last;
	int	option;

	while (size_b > 0)
	{
		b_first = *(int *)((*b)->content);
		a_last = *(int *)((ft_lstlast(*a))->content);
		option = pa_or_rra(*a, b_first, a_last);
		if (option == 1)
		{
			push(a, b);
			ft_printf("pa\n");
		}
		else
		{
			reverse_rotate(a);
			ft_printf("rra\n");
		}
		size_b = ft_lstsize(*b);
	}
}

/*Funcion que calcula los movimientos y la direccion para tener max arriba de
la lista*/
static int	move_max(t_list *lst, int max, int size, t_mov_properties *new)
{
	int	i;

	new->dir_b = -1;
	i = 0;
	while ((*(int *)(lst->content)) != max)
	{
		i++;
		lst = lst->next;
	}
	if ((size - i) < i)
	{
		i = size - i;
		new->dir_b = 1;
	}
	return (i);
}

/*Funcion que devuelve la lista b organizada con el max arriba y en la menor
cantidad de mov posibles*/
static void	organize_b(t_list **lst, int size)
{
	int					max;
	int					i;
	t_mov_properties	new_mov;

	max = ft_lstmax(*lst);
	i = move_max(*lst, max, size, &new_mov);
	while (i > 0)
	{
		if (new_mov.dir_b == 1)
		{
			reverse_rotate(lst);
			ft_printf("rrb\n");
		}
		if (new_mov.dir_b == -1)
		{
			rotate(lst);
			ft_printf("rb\n");
		}
		i--;
	}
}

/*Funcion que traspasa todos los numeros de la lista b a la lista a (que aun 
tiene 3 elementos)*/
void	organize(t_list **a, t_list **b)
{
	int	size_b;
	int	min;

	size_b = ft_lstsize(*b);
	organize_b(b, size_b);
	organize_a(a, b, size_b);
	min = ft_lstmin(*a);
	while (min != *(int *)((*a)->content))
	{
		reverse_rotate(a);
		ft_printf("rra\n");
	}
}
