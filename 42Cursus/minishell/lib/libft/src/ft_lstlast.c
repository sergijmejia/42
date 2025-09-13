/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:44:46 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/08 09:34:07 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (ft_lstlast(lst->next));
}
/*
int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;
	t_list	*pnt;
	
	first = ft_lstnew("first");
	second = ft_lstnew("second");
	third = ft_lstnew("third");
	first->next = second;
	second->next = third;
	third->next = NULL;
	pnt = ft_lstlast(first);
	printf("El texto en el ultimo puntero es: %s\n", (char *) pnt->content);
	return (0);
}
*/
