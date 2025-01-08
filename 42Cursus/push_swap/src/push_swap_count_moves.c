/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_count_moves.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:41:14 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/23 12:24:24 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ************************  FUNCIONES  COUNT_MOVES  ************************ */

/*Devuelve la cantidad de movimientos necesarios en lst hasta max*/
static int	moves_to_max(t_list *lst)
{
	t_list	*pnt;
	int		moves;
	int		boolean;
	int		max;

	moves = 0;
	boolean = 1;
	max = ft_lstmax(lst);
	pnt = lst;
	while (boolean)
	{
		if ((*(int *)(pnt->content)) == max)
			break ;
		pnt = pnt->next;
		moves++;
	}
	return (moves);
}

/*Devuelve la cantidad de movimientos necesarios para unicar correctamente x en
la lista lst*/
static int	moves_to_x(t_list *lst, int x)
{
	int		x_1;
	int		x_2;
	int		moves;
	int		boolean;
	t_list	*pnt;

	pnt = lst;
	boolean = 1;
	moves = 0;
	while (boolean)
	{
		moves++;
		x_1 = *(int *)(pnt->content);
		if (pnt->next)
			x_2 = *(int *)((pnt->next)->content);
		else
			x_2 = *(int *)(lst->content);
		if (x <= x_1 && x >= x_2)
			break ;
		pnt = pnt->next;
	}
	return (moves);
}

/*Cuenta cuantos movimientos se han de hacer en lst para organizar correctamente
x habiendo desplazado moves posiciones previamente*/
int	count_moves_b(t_list *lst, int x, int moves)
{
	int		size;
	int		i;
	int		j;
	int		min;
	int		max;

	size = ft_lstsize(lst);
	min = ft_lstmin(lst);
	max = ft_lstmax(lst);
	i = 0;
	if (x < min || x > max)
		i = moves_to_max(lst);
	else if (*(int *)(lst->content) >= x)
		i = moves_to_x(lst, x);
	else if (x >= *(int *)(ft_lstlast(lst)->content))
		i = moves_to_x(lst, x);
	i = (i + moves) % size;
	j = size - i;
	if (i >= j)
		return (j);
	else
		return ((-1) * i);
}

/*Cuenta la cantidad de movimientos que se han de hacer para llevar la posicion
x hasta la primera posicion siguiendo una determinada direccion dir*/
int	count_moves_a(t_list *lst, int pos, int dir)
{
	int	size;

	if (lst == NULL)
		return (0);
	size = ft_lstsize(lst);
	if (pos == 0 || dir == -1)
		return (pos);
	else
		return (size - pos);
}
