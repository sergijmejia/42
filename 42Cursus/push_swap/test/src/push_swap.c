/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:07:20 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/06 22:36:54 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* **************************  FUNCION  PUSH_SWAP  ************************** */

/*Funcion qu vacia la lista lst e imprime "Error" por el fd 2*/
static int	ft_error(t_list *lst)
{
	ft_lstclear(&lst, free);
	write(2, "Error\n", 6);
	return (1);
}

/*Funcion principal push_swap*/
int	push_swap(t_list **a, t_list **b)
{
	int	size;
	int	init_size;

	init_size = ft_lstsize(*a);
	if (init_size == 1)
		return (1);
	if (init_size > 2)
	{
		push(b, a);
		ft_printf("pb\n");
		if (init_size > 3)
		{
			push(b, a);
			ft_printf("pb\n");
			size = init_size - 2;
			while (size > 2)
			{
				min_move(a, b);
				size = ft_lstsize(*a);
			}
		}
	}
	if ((*(int *)((*a)->content)) > (*(int *)(((*a)->next)->content)))
	{
		swap(a);
		ft_printf("sa\n");
	}
	if (init_size > 2)
		organize(a, b);
	return (1);
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
	if (!organized_lst(a))
		push_swap(&a, &b);
	else
	{
		while ((*(int *)(a->content)) != (ft_lstmin(a)))
		{
			reverse_rotate(&a);
			ft_printf("rra\n");
		}
	}
	ft_lstclear(&a, free);
	return (0);
}
