/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:42:42 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:04:17 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Adds a node at the beginning of the list
// PARAMETERS:
// - t_list **lst: Pointer to the head of the list
// - t_list *new: Node to be added at the front
// DESCRIPTION:
// - Sets the new node's next pointer to the current head of the list.
// - Updates the head to point to the new node.
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
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

    ft_lstadd_front(&list, node1);
    ft_lstadd_front(&list, node2);
    ft_lstadd_front(&list, node3);

    printf("List after adding nodes to the front:\n");
    for (t_list *current = list; current; current = current->next)
    {
        printf("%s\n", (char *)current->content);
    }

    ft_lstclear(&list, free);
    return 0;
}
*/
