/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:32:39 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/10 15:58:12 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>

void	*test_function(void *str)
{
	char	*aux;

	if (str == NULL)
		return (NULL);
	aux = (char *)str;
	while (*aux)
	{
		*aux = ft_toupper(*aux);
		aux++;
	}
	return (str);
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**pnt;
	t_list	*f_lst;
	t_list	*aux;

	if ((lst == NULL) || (f == NULL) || (del == NULL))
		return (NULL);
	f_lst = NULL;
	pnt = &f_lst;
	while (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (aux == NULL)
		{
			ft_lstclear(pnt, del);
			return (NULL);
		}
		ft_lstadd_back(pnt, aux);
		lst = lst->next;
	}
	return (f_lst);
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
	t_list	*temp;
	void	*pntf;
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
	printf("La longitud de la lista original es %d\n", ft_lstsize(lst));
	printf("la lista original es:\n");
	temp = lst;
	while (temp)
	{
		printf("%s\n", (char *)(temp->content));
		temp = temp->next;
	}
	pntf = &test_function;
	lst2 = ft_lstmap(lst, pntf, free);
	printf("La longitud de la nueva lista es %d\n", ft_lstsize(lst2));
	printf("la nueva es:\n");
	while (lst2)
	{
		printf("%s\n", (char *)((lst2)->content));
		lst2 = lst2->next;
	}
	return (0);
}
*/
