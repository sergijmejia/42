/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:47:30 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:04:27 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Deletes and frees all nodes from the given node to the end
// PARAMETERS:
// - t_list **lst: Pointer to the head of the list
// - void (*del)(void *): Function to free the content of each node
// DESCRIPTION:
// - Uses ft_lstdelone to free the content and the node itself for each node.
// - Sets the head of the list to NULL after clearing all nodes.
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (lst && del)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			ft_lstdelone(current, del);
			current = next;
		}
		*lst = NULL;
	}
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

    printf("List before clearing:\n");
    for (t_list *current = list; current; current = current->next)
    {
        printf("%s\n", (char *)current->content);
    }

    ft_lstclear(&list, free);
    printf("List cleared. Size after clearing: %d\n",
			ft_lstsize(list)); // Should be 0

    return 0;
}
*/
