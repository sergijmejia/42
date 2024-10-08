/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:25:41 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/08 14:53:34 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;
	t_list	*begin;

	if ((lst == NULL) || (*lst == NULL) || (del == NULL))
		return ;

	begin = *lst;
	while (begin != NULL)
	{
		aux = (begin)->next;
		ft_lstdelone((begin), del);
		(begin) = aux;
	}
	*lst = begin;
}
/*
int main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;
	t_list	**pnt;
	t_list	*lst;

	lst = NULL;
	first = ft_lstnew("first");
	second = ft_lstnew("second");
	third = ft_lstnew("third");
	pnt = &lst;
	ft_lstadd_back(pnt, first);
	ft_lstadd_back(pnt, second);
	ft_lstadd_back(pnt, third);
	printf("La longitud de la lista antes de ft es %d\n", ft_lstsize(*pnt));
	ft_lstclear(pnt, free);
	printf("La longitud de la lista despues de ft es %d\n", ft_lstsize(*pnt));
	return (0);
}
*/
