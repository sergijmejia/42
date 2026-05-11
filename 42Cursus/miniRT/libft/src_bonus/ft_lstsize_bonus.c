/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:43:26 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:05:53 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Counts the number of nodes in the list
// PARAMETERS:
// - t_list *lst: Pointer to the head of the list
// RETURNS:
// - The number of nodes in the list
// DESCRIPTION:
// - Iterates through the list, counting each node until the end.
int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    t_list *list = NULL;
    ft_lstadd_back(&list, ft_lstnew("Node 1"));
    ft_lstadd_back(&list, ft_lstnew("Node 2"));
    ft_lstadd_back(&list, ft_lstnew("Node 3"));

    int size = ft_lstsize(list);
    printf("Size of list: %d\n", size); // Should print 3

    ft_lstclear(&list, free);
    return 0;
}
*/
