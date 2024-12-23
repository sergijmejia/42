/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_setters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:34:29 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/23 12:52:59 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* **************************  FUNCIONES  SETTERS  ************************** */

/*Asigna el valor a direction_b*/
int	set_direction_b(int moves_dir)
{
	if (moves_dir < 0)
		return (-1);
	else
		return (1);
}

/*Modifica el valor de moves, direction_b y result en caso de haber obtenido un
move menor*/
int	set_result(t_mov_properties *new_mov, int i)
{
	new_mov->mov_b = ft_abs(new_mov->mov_b_dir);
	new_mov->mov = new_mov->mov_a + new_mov->mov_b;
	new_mov->dir_b = set_direction_b(new_mov->mov_b_dir);
	return (i);
}

/*Asigna valor a direction_a*/
int	set_direction_a(int old_direction_a, int result)
{
	if (result == 0)
		return (old_direction_a);
	if (result == -1 || result == 1 || result == 2)
		return (-1);
	else
		return (1);
}

/*Asigna el valor a rotate*/
int	set_rotate(int old_rotate, int result)
{
	if (result == 0)
		return (old_rotate);
	if (result == -1 || result == 2 || result == 4)
		return (0);
	else
		return (1);
}

/*Asigna el valor a pos*/
int	set_pos(t_list **a, int old_pos, int result, int i)
{
	if (result == -1)
		return (0);
	if (result == 0)
		return (old_pos);
	if (result == 1 | result == 2)
		return (i);
	else
		return (ft_lstsize(*a) - i);
}
