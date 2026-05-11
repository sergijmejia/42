/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:44:54 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:04:01 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Adds a node at the end of the list
// PARAMETERS:
// - t_list **lst: Pointer to the head of the list
// - t_list *new: Node to be added at the end
// DESCRIPTION:
// - If the list is empty, the new node becomes the first node.
// - Otherwise, the function traverses to the last node using ft_lstlast
//   and sets the next pointer of the last node to the new node.
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst && new)
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    t_list *list = NULL;
    t_list *node1 = ft_lstnew("First node");
    t_list *node2 = ft_lstnew("Second node");
    t_list *node3 = ft_lstnew("Third node");

    ft_lstadd_back(&list, node1);
    ft_lstadd_back(&list, node2);
    ft_lstadd_back(&list, node3);

    printf("List after adding nodes to the back:\n");
    for (t_list *current = list; current; current = current->next)
    {
        printf("%s\n", (char *)current->content);
    }

    ft_lstclear(&list, free);
    return 0;
}
*/
