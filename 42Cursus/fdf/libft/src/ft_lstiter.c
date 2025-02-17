/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:33:11 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/09 10:45:45 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;
	t_list	**pnt;
	t_list	*lst;
	t_list	*lst2;
	char	aux1[7];
	char    aux2[7];
	char    aux3[7];

	lst = NULL;
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
	printf("La lista es:\n");
	while (lst2)
	{
		printf("%s\n", (char *)(lst2->content));
		lst2 = lst2->next;
	}
	ft_lstiter(*pnt, ft_strtoupper);
	printf("La lista despues de ft_lstiter es:\n");
	while (lst)
	{
		printf("%s\n", (char *)(lst->content));
		lst = lst->next;
	}
	return (0);
}
*/
