/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_do_moves.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:14:58 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/23 12:19:15 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* **************************  FUNCIONES DO_MOVES  ************************** */

/*Realiza los movimientos de la lista a en direccion negativa*/
static void	move_a_neg(t_list **a, t_list **b, int pos, int rot)
{
	while (pos > 0)
	{
		pos--;
		if (rot == 0)
		{
			rotate(a);
			ft_printf("ra\n");
		}
		else
		{
			rotate_rotate(a, b);
			ft_printf("rr\n");
		}
	}
}

/*Realiza los movimientos de la lista a en direccion positiva*/
static void	move_a_pos(t_list **a, t_list **b, int pos, int rot)
{
	int	size;

	size = ft_lstsize(*a);
	while (size - pos > 0)
	{
		pos++;
		if (rot == 0)
		{
			reverse_rotate(a);
			ft_printf("rra\n");
		}
		else
		{
			reverse_rotate_rotate(a, b);
			ft_printf("rrr\n");
		}
	}
}

/*Realiza los movimientos de la lista b*/
static void	move_b(t_list **a, t_list **b, int direction)
{
	int	moves;

	moves = ft_abs(count_moves_b(*b, *(int *)((*a)->content), 0));
	while (moves > 0)
	{
		if (direction == 1)
		{
			reverse_rotate(b);
			ft_printf("rrb\n");
		}
		else
		{
			rotate(b);
			ft_printf("rb\n");
		}
		moves--;
	}
}

/*Realiza los movimientos de a con los datos transferidos*/
void	do_moves_a(t_list **a, t_list **b, t_mov_properties new_mov)
{
	int	size_a;

	size_a = ft_lstsize(*a);
	if (new_mov.dir_a == -1)
		move_a_neg(a, b, new_mov.pos, new_mov.rotate);
	if (new_mov.dir_a == 1)
		move_a_pos(a, b, new_mov.pos, new_mov.rotate);
}

/*Realiza los movimientos de b con los datos transferidos*/
void	do_moves_b(t_list **a, t_list **b, t_mov_properties new_mov)
{
	move_b(a, b, new_mov.dir_b);
	ft_printf("pb\n");
	push(b, a);
}
