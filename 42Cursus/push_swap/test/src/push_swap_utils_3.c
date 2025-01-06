/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:15:12 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/06 22:57:55 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Verifica quue la lista lst no este organizada ya*/
int	organized_lst(t_list *lst)
{
	int	max;
	int	min;
	int	first;
	int	current;

	if (ft_lstsize(lst) == 1)
		return (1);
	max = ft_lstmax(lst);
	min = ft_lstmin(lst);
	first = *(int *)(lst->content);
	current = first;
	lst = lst->next;
	while (lst)
	{
		if (current > *(int *)(lst->content))
		{
			if (current != max || (*(int *)(lst->content) != min))
				return (0);
		}
		current = *(int *)(lst->content);
		lst = lst->next;
	}
	if (current > first && current != max)
		return (0);
	return (1);
}
