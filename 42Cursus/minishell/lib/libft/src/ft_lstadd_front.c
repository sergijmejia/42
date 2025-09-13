/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:52:53 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/09 10:48:09 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if ((lst == NULL) || (new == NULL))
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;
	t_list	**pnt;

	first = ft_lstnew("first");
	if (!first)
		return (1);
	second = ft_lstnew("second");
	if (!second)
		return (1);
	third = ft_lstnew("third");
	if (!third)
		return (1);
	second->next = third;
	pnt = &second;
	ft_lstadd_front(pnt, first);
	printf("El texto en el primer nodo es: %s\n", (char *) (*pnt)->content);
	//ft_lstclear(pnt, free);
	return (0);
}
*/
