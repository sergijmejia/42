/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:45:55 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:04:42 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Frees the memory of the content and the node
// PARAMETERS:
// - t_list *lst: Node to be deleted
// - void (*del)(void *): Function to free the content of the node
// DESCRIPTION:
// - Uses the del function to free the content, then frees the node itself.
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    t_list *node = ft_lstnew("Node to delete");
    printf("Deleting node with content: %s\n", (char *)node->content);
    ft_lstdelone(node, free);

    // Try to print content after deletion
    if (node == NULL)
        printf("Node has been deleted.\n");

    return 0;
}
*/
