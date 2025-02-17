/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:35:53 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/09 10:52:30 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	if ((lst == NULL) || (new == NULL))
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		aux = ft_lstlast(*lst);
		aux->next = new;
	}
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
	first->next = second;
	pnt = &first;
	ft_lstadd_back(pnt, third);
	printf("El texto en el ultimo puntero es: ");
	printf("%s\n", (char *)(ft_lstlast(*pnt))->content);
	free(first);
	free(second);
	free(third);
	return (0);
}
*/
