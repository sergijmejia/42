/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:31:19 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/09 11:07:09 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Funcion que vacia las listas a y b e imprime "OK" por el fd 1*/
int	ft_ko(t_list **a, t_list **b)
{
	ft_lstclear(a, free);
	ft_lstclear(b, free);
	write(1, "KO\n", 3);
	return (1);
}

/*Funcion que vacia las listas a y b e imprime "OK" por el fd 1*/
int	ft_ok(t_list **a, t_list **b)
{
	ft_lstclear(a, free);
	ft_lstclear(b, free);
	write(1, "OK\n", 3);
	return (1);
}

/*Funcion que aplica los movimientos sa sb ss pa pb ra rb rr*/
int	functions_two_len(t_list **a, t_list **b, char *str)
{
	if (ft_strncmp("sa\n", str, 3) == 0)
		swap(a);
	else if (ft_strncmp("sb\n", str, 3) == 0)
		swap(b);
	else if (ft_strncmp("ss\n", str, 3) == 0)
		swap_swap(a, b);
	else if (ft_strncmp("pa\n", str, 3) == 0)
		push(a, b);
	else if (ft_strncmp("pb\n", str, 3) == 0)
		push(b, a);
	else if (ft_strncmp("ra\n", str, 3) == 0)
		rotate(a);
	else if (ft_strncmp("rb\n", str, 3) == 0)
		rotate(b);
	else if (ft_strncmp("rr\n", str, 3) == 0)
		rotate_rotate(a, b);
	else
		return (-1);
	return (1);
}

int	functions_three_len(t_list **a, t_list **b, char *str)
{
	if (ft_strncmp("rra\n", str, 4) == 0)
		reverse_rotate(a);
	else if (ft_strncmp("rrb\n", str, 4) == 0)
		reverse_rotate(b);
	else if (ft_strncmp("rrr\n", str, 4) == 0)
		reverse_rotate_rotate(a, b);
	else
		return (-1);
	return (1);
}
