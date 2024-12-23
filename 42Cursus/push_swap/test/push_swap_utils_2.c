/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:04:25 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/23 13:05:21 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* *************************  FUNCIONES AUXILIARES  ************************* */

/*Devuelve un puntero a la posicion x de la lista lst*/
t_list	*ft_lstpos(t_list *lst, int x)
{
	int		size;
	int		i;
	t_list	*pnt;

	size = ft_lstsize(lst);
	if (x >= size || x < 0)
		return (NULL);
	pnt = lst;
	i = 0;
	while (i < x)
	{
		pnt = pnt->next;
		i++;
	}
	return (pnt);
}

/*Devuelve un puntero al penultimo elemmento de la lista lst*/
t_list	*ft_lstsecondlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (NULL);
	if ((lst->next)->next == NULL)
		return (lst);
	return (ft_lstsecondlast(lst->next));
}

/*Devuelve un puntero a un duplicado de la lista lst*/
t_list	*ft_lstdup(t_list *lst)
{
	t_list	*new_lst;
	int		len;

	if (lst == NULL)
		return (NULL);
	len = ft_lstsize(lst);
	new_lst = malloc (sizeof(t_list));
	if (new_lst == NULL)
	{
		return (NULL);
	}
	new_lst->content = lst->content;
	new_lst->next = ft_lstdup(lst->next);
	if (ft_lstsize(new_lst) != len)
	{
		ft_lstclear(&new_lst, free);
		return (NULL);
	}
	return (new_lst);
}

/*Imprime por pantalla la lista lst*/
void	print_lst(t_list *lst)
{
	if (lst == NULL)
		return ;
	ft_printf("%d ", *(int *)(lst->content));
	if (lst->next != NULL)
	{
		print_lst(lst->next);
		return ;
	}
}

/*Imprime por pantalla las dos listas a y b*/
void	print_ab_lists(t_list *a, t_list *b)
{
	ft_printf("Lista a: ");
	print_lst(a);
	ft_printf("\nLista b: ");
	print_lst(b);
	ft_printf("\n");
}
