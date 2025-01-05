/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:42:23 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/05 12:54:44 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* *************************  FUNCIONES AUXILIARES  ************************* */

/*Funcion para avanzar en un string str todos los espacios, tabuladores, ect.*/
static void	move_pnt_to_next(char **str)
{
	while ((**str >= '\t' && **str <= '\r') || **str == ' ')
		(*str)++;
}

/*Crea la lista de enteros lst a partir del string str*/
t_list	*create_list(t_list **lst, char *str)
{
	int		*new_num;
	t_list	*new_node;

	move_pnt_to_next(&str);
	while (*str != '\0')
	{
		if (ft_atol(str) < INT_MIN || ft_atol(str) > INT_MAX)
			return (ft_free_lst(lst));
		new_num = (int *) malloc (sizeof(int));
		if (!new_num)
			return (ft_free_lst(lst));
		new_num[0] = ft_atoi(str);
		new_node = ft_lstnew(new_num);
		if (!new_node)
		{
			free(new_num);
			return (ft_free_lst(lst));
		}
		ft_lstadd_back(lst, new_node);
		while (*str == '-' || *str == '+' || ft_isdigit(*str))
			str++;
		move_pnt_to_next(&str);
	}
	return (*lst);
}

/*Funcion para limpiar listas*/
t_list	*ft_free_lst(t_list **lst)
{
	ft_lstclear(lst, free);
	return (*lst);
}

/*Devuelve el valor minimo de la lista*/
int	ft_lstmin(t_list *lst)
{
	int	min;

	min = *(int *)(lst->content);
	while (lst->next)
	{
		lst = lst->next;
		if (min > *(int *)(lst->content))
			min = *(int *)(lst->content);
	}
	return (min);
}

/*Devuelve el valor maximo de la lista*/
int	ft_lstmax(t_list *lst)
{
	int	max;

	max = *(int *)(lst->content);
	while (lst->next)
	{
		lst = lst->next;
		if (max < *(int *)(lst->content))
			max = *(int *)(lst->content);
	}
	return (max);
}
