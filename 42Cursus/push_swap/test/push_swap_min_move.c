/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_min_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:58:14 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/23 12:51:54 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ***************************  FUNCION MIN_MOVE  *************************** */

/*Calcula si es mas eficiente utilizar rotate o no*/
static int	rotate_definition(t_list **a, t_list **b, int moves, int i)
{
	int	moves_a;
	int	moves_b;
	int	num_b;
	int	rotate;

	moves_a = count_moves_a(*a, i, -1);
	num_b = *(int *)(ft_lstpos(*a, i)->content);
	moves_b = ft_abs(count_moves_b(*b, num_b, (-1) * moves_a));
	if ((moves_a + moves_b) < moves)
		rotate = 1;
	moves_b = ft_abs(count_moves_b(*b, num_b, 0));
	if ((moves_a + moves_b) < moves)
		rotate = 0;
	return (rotate);
}

/*Calcula la minima combinacion de move_a y move_b*/
static int	min_mov_ab(t_list **a, t_list **b, int i, t_mov_properties *new)
{
	int	num_b;
	int	result;

	if (i == 0)
		return (-1);
	result = 0;
	new->mov_a = count_moves_a(*a, i, -1);
	num_b = *(int *)(ft_lstpos(*a, i)->content);
	new->mov_b_dir = count_moves_b(*b, num_b, (-1) * new->mov_a);
	if ((new->mov_a) + ft_abs(new->mov_b_dir) < (new->mov))
		result = set_result(new, 1);
	new->mov_b_dir = count_moves_b(*b, num_b, 0);
	if ((new->mov_a) + ft_abs(new->mov_b_dir) < (new->mov))
		result = set_result(new, 2);
	new->mov_a = count_moves_a(*a, ft_lstsize(*a) - i, 1);
	num_b = *(int *)(ft_lstpos(*a, ft_lstsize(*a) - i)->content);
	new->mov_b_dir = count_moves_b(*b, num_b, new->mov_a);
	if ((new->mov_a) + ft_abs(new->mov_b_dir) < (new->mov))
		result = set_result(new, 3);
	new->mov_b_dir = count_moves_b(*b, num_b, 0);
	if ((new->mov_a) + ft_abs(new->mov_b_dir) < (new->mov))
		result = set_result(new, 4);
	return (result);
}

/*Cuenta los movimientos necesarios para pasar un elemento de la lista a a la
lista b. Se calcula con el elemento que requiera menor cantidad de movimientos*/
void	min_move(t_list **a, t_list **b)
{
	int					i;
	int					option;
	t_mov_properties	new_mov;

	if ((count_moves_b(*b, (*(int *)((*a)->content)), 0)) < 0)
		new_mov.dir_b = -1;
	else
		new_mov.dir_b = 1;
	new_mov.pos = 0;
	new_mov.mov = ft_abs(count_moves_b(*b, (*(int *)((*a)->content)), 0));
	i = 0;
	while ((i < new_mov.mov && i < ft_lstsize(*a)) || new_mov.mov == 0)
	{
		option = min_mov_ab(a, b, i, &new_mov);
		new_mov.pos = set_pos(a, new_mov.pos, option, i);
		new_mov.dir_a = set_direction_a(new_mov.dir_a, option);
		new_mov.rotate = set_rotate(new_mov.rotate, option);
		if (i >= (ft_lstsize(*a) / 2))
			break ;
		i++;
	}
	do_moves_a(a, b, new_mov);
	do_moves_b(a, b, new_mov);
}
