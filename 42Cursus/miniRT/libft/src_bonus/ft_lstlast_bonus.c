/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:44:17 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:05:13 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Returns the last node of the list
// PARAMETERS:
// - t_list *lst: Pointer to the head of the list
// RETURNS:
// - Pointer to the last node, or NULL if the list is empty
// DESCRIPTION:
// - Traverses the list until it finds the last node (where next is NULL).
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    t_list *list = NULL;
    ft_lstadd_back(&list, ft_lstnew("First node"));
    ft_lstadd_back(&list, ft_lstnew("Second node"));
    ft_lstadd_back(&list, ft_lstnew("Third node"));

    t_list *last = ft_lstlast(list);
    if (last)
        printf("Last node content: %s\n", (char *)last->content);

    ft_lstclear(&list, free);
    return 0;
}
*/
