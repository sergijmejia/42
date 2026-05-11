/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:49:33 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:05:24 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Helper function to create a new node with transformed content.
// PARAMETERS:
// - void *(*f)(void *): Function to transform the content of the node.
// - void *content: The original content of the node.
// RETURNS:
// - A pointer to the newly created node, or NULL if creation fails.
static t_list	*create_new_node(void *(*f)(void *), void *content)
{
	void	*new_content;
	t_list	*new_node;

	new_content = f(content);
	if (!new_content)
		return (NULL);
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		free(new_content);
		return (NULL);
	}
	return (new_node);
}

// Creates a new list by applying a function to each node's content
// PARAMETERS:
// - t_list *lst: Pointer to the head of the list
// - void *(*f)(void *): Function to transform each node's content
// - void (*del)(void *): Function to free the content if needed
// RETURNS:
// - Pointer to the new list, or NULL if an error occurs
// DESCRIPTION:
// - Iterates through the list, applying f to each node's content and creating
//   a new list with the transformed content.
// - If a node creation fails, clears the entire new list using ft_lstclear.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = create_new_node(f, lst->content);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdio.h>
#include <stdlib.h>
void *transform_content(void *content)
{
    char *new_content = malloc(20);
    snprintf(new_content, 20, "%s transformed", (char *)content);
    return new_content;
}

int main(void)
{
    t_list *list = NULL;
    ft_lstadd_back(&list, ft_lstnew("Node 1"));
    ft_lstadd_back(&list, ft_lstnew("Node 2"));

    t_list *mapped_list = ft_lstmap(list, transform_content, free);

    printf("Mapped list contents:\n");
    for (t_list *current = mapped_list; current; current = current->next)
    {
        printf("%s\n", (char *)current->content);
    }

    ft_lstclear(&list, free);
    ft_lstclear(&mapped_list, free);
    return 0;
}
*/
