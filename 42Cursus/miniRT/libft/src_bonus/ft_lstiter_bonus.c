/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:48:20 by rafaguti          #+#    #+#             */
/*   Updated: 2025/02/21 16:05:01 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_bonus.h"

// Applies a function to each node in the list
// PARAMETERS:
// - t_list *lst: Pointer to the head of the list
// - void (*f)(void *): Function to apply to each node's content
// DESCRIPTION:
// - Iterates through the list applying the function to the content of each node
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
#include <stdlib.h>
void print_content(void *content)
{
    printf("%s\n", (char *)content);
}

int main(void)
{
    t_list *list = NULL;
    ft_lstadd_back(&list, ft_lstnew("Node 1"));
    ft_lstadd_back(&list, ft_lstnew("Node 2"));
    ft_lstadd_back(&list, ft_lstnew("Node 3"));

    printf("List contents:\n");
    ft_lstiter(list, print_content);

    ft_lstclear(&list, free);
    return 0;
}
*/
