/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:29:25 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/03 15:53:48 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Funciones de movimiento del push swap*/

static void	swap(t_list **lst)
{
	t_list	*aux1;
	t_list	*aux2;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	aux1 = *lst;
	aux2 = (*lst)->next;
	aux1 = aux2->next;
	aux2->next = aux1;
	*lst = aux2;
}


static t_list	*ft_lstdup(t_list *lst)
{
	t_list	*new_lst;
	int	len;

	if(lst == NULL)
		return (NULL);
	len = ft_lstsize(lst);
	new_lst = malloc (sizeof(t_list));
	if(new_lst == NULL)
	{
		return (NULL);
	}
	new_lst->content = lst->content;
	new_lst->next = ft_lstdup(lst->next);
	if(ft_lstsize(new_lst) != len)
	{
		ft_lstclear(&new_lst, free);
		return (NULL);
	}
	return (new_lst);
}	

static void	print_lst(t_list *lst)
{
	if (lst == NULL)
		return ;
	ft_printf("%d ", lst->content);
	if (lst->next == NULL)
		return ;
	else
	{
		print_lst(lst->next);
		return ;
	}
}

int	push_swap(t_list **a)
{
	//*lst->content es el numero en la posicion 1
	//*lst->next apunta al siguiente elemento
	
	int		len;
	int		result;
	//t_list	*b;
	t_list	*lst;

	result = 0;
	len = ft_lstsize(*a);
	lst = ft_lstdup(*a);
	if(lst == NULL)
		return (0); //ESTO SE DEBE REVISAR
	print_lst(*a);
	ft_printf("\n");
	print_lst(lst);
	ft_printf("\n");
	swap(&lst);
	print_lst(lst);
	return (1);
}
