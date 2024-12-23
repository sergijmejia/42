/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:07:20 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/23 12:56:42 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* **************************  FUNCION  PUSH_SWAP  ************************** */

int	push_swap(t_list **a, t_list **b)
{
	int	size;

	push(b, a);
	push(b, a);
	ft_printf("pb\n");
	ft_printf("pb\n");
	size = ft_lstsize(*a);
	while (size > 2)
	{
		min_move(a, b);
		size = ft_lstsize(*a);
	}
	if ((*(int *)((*a)->content)) > (*(int *)(((*a)->next)->content)))
	{
		swap(a);
		ft_printf("sa\n");
	}
	organize(a, b);
	return (1);
}

/*Programa main principal*/
int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	char	*str;

	if (argc != 2)
		return (1);
	a = NULL;
	b = NULL;
	str = argv[1];
	if (!check_error(str))
		return (1);
	create_list(&a, str);
	if (!a)
	{
		ft_printf("Error\n");
		return (1);
	}
	push_swap(&a, &b);
	ft_printf("\n");
	ft_lstclear(&a, free);
	return (0);
}
