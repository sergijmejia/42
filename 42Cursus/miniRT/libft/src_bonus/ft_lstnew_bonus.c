/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:41:11 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:05:43 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Creates a new node
// PARAMETERS:
// - void *content: Content to store in the new node
// RETURNS:
// - Pointer to the new node, or NULL if memory allocation fails
// DESCRIPTION:
// - Allocates memory for new node and sets its content and next pointer to NULL
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    char *content = malloc(20);
    snprintf(content, 20, "New Node Content");

    t_list *node = ft_lstnew(content);
    if (node)
    {
        printf("New node created with content: %s\n", (char *)node->content);
    }

    ft_lstdelone(node, free);
    return 0;
}
*/
