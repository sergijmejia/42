/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:42:23 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/04 13:14:45 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* *************************  FUNCIONES AUXILIARES  ************************* */

/*Funcion para limpiar listas*/
t_list	*ft_free_lst(t_list **lst)
{
	ft_lstclear(lst, free);
	return (*lst);
}

/*Verifica que la lista de enteros de entrada no contiene caracteres no 
admitidos*/
int	check_error_str(char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str) && !(*str >= '\t' && *str <= '\r'))
		{
			if (*str != '+' && *str != '-' && *str != ' ')
				return (0);
		}
		str++;
	}
	return (1);
}

/*Crea la lista de enteros lst a partir del string str*/
t_list	*create_list(t_list **lst, char *str)
{
	int		*new_num;
	t_list	*new_node;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	while (*str != '\0')
	{
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
		while (*str == 45 || *str == 43 || (*str >= 48 && *str <= 57))
			str++;
		while ((*str >= '\t' && *str <= '\r') || *str == ' ')
			str++;
	}
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
