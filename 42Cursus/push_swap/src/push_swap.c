/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:07:20 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/09 16:11:50 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* **************************  FUNCION  PUSH_SWAP  ************************** */

/*Funcion que hace girar una lista organizada de tres elementos hasta tener el
min en la primera posicion*/
static	void	organize_min_lst(t_list **lst)
{
	while ((*(int *)((*lst)->content)) != (ft_lstmin(*lst)))
	{
		reverse_rotate(lst);
		ft_printf("rra\n");
	}
}

/*Funcion que vacia la lista lst e imprime "Error" por el fd 2*/
static int	ft_error(t_list *lst)
{
	ft_lstclear(&lst, free);
	write(2, "Error\n", 6);
	return (1);
}

/*Funcion que mueve de forma ordenada elementos a la lista b hasta tener
max tres elementos en a*/
static void	move_b_multiple_elements(t_list **a, t_list **b, int init_size)
{
	int	size;

	push(b, a);
	ft_printf("pb\n");
	if (init_size > 4)
	{
		push(b, a);
		ft_printf("pb\n");
		size = init_size - 2;
		while (size > 3)
		{
			min_move(a, b);
			size = ft_lstsize(*a);
		}
	}
}

/*Funcion principal push_swap*/
void	push_swap(t_list **a, t_list **b)
{
	int	init_size;

	if (organized_lst(*a))
	{
		organize_min_lst(a);
		return ;
	}
	init_size = ft_lstsize(*a);
	if (init_size == 1)
		return ;
	if (init_size > 3)
		move_b_multiple_elements(a, b, init_size);
	if (!organized_lst(*a))
	{
		swap(a);
		ft_printf("sa\n");
		organize_min_lst(a);
	}
	if (init_size > 3)
		organize(a, b);
}

/*Programa main principal*/
int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	char	*str;
	int		i;

	a = NULL;
	b = NULL;
	i = 1;
	if (argc < 2)
		return (1);
	while (i < argc)
	{
		str = argv[i];
		if (!check_error_str(str))
			return (ft_error(a));
		create_list(&a, str);
		if (!a)
			return (ft_error(a));
		i++;
	}
	if (check_error_lst(a) == -1)
		return (ft_error(a));
	push_swap(&a, &b);
	ft_lstclear(&a, free);
	return (0);
}
