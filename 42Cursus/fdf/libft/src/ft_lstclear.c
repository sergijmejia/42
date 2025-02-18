/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:25:41 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/18 09:48:14 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	while (*lst != NULL)
	{
		aux = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = aux;
	}
	*lst = NULL;
}
/*
int main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;
	t_list	**pnt;
	t_list	*lst;
	t_list	*lst2;
	char	*aux1;
	char    *aux2;
	char    *aux3;

	lst = NULL;
	aux1 = (char *) malloc (7);
	aux2 = (char *) malloc (7);
	aux3 = (char *) malloc (7);
	ft_strlcpy(aux1, "first", 7); 
	first = ft_lstnew(aux1);
	ft_strlcpy(aux2, "second", 7);
	second = ft_lstnew(aux2);
	ft_strlcpy(aux3, "third", 7);
	third = ft_lstnew(aux3);
	pnt = &lst;
	ft_lstadd_back(pnt, first);
	ft_lstadd_back(pnt, second);
	ft_lstadd_back(pnt, third);
	lst2 = lst;
	printf("La longitud de la lista antes de ft es %d\n", ft_lstsize(lst2));
	ft_lstclear(pnt, free);
	printf("La longitud de la lista despues de ft es %d\n", ft_lstsize(lst));
	return (0);
}
*/
