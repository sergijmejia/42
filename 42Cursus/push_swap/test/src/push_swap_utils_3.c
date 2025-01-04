/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:53:32 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/04 16:02:04 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Copia una lista de numeros a un string de numeros*/
static int	*cpy_lst(t_list *lst)
{
	int	i;
	int	*lst_sorted;
	int	size;

	size = ft_lstsize(lst);
	lst_sorted = (int *) malloc (size * sizeof(int));
	if (lst_sorted == NULL)
		return (NULL);
	i = 0;
	while (lst != NULL)
	{
		lst_sorted[i] = *(int *)(lst->content);
		i++;
		lst = lst->next;
	}
	return (lst_sorted);
}

/*Organiza un string de numeros mediante el metodo de organizacion burbuja*/
static int	*bubble_sort(int *num, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < (size - i - 1))
		{
			if (num[j] > num[j + 1])
			{
				temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (num);
}

/*Verifica que la lista lst no tenga elementos duplicados*/
static int	check_duplicate(t_list *lst)
{
	int	*lst_sorted;
	int	i;
	int	size;

	lst_sorted = cpy_lst(lst);
	if (lst_sorted == NULL)
		return (-1);
	size = ft_lstsize(lst);
	lst_sorted = bubble_sort(lst_sorted, size);
	i = 0;
	while (i < size)
	{
		if (lst_sorted[i] == lst_sorted[i + 1])
		{
			free(lst_sorted);
			return (-1);
		}
		i++;
	}
	free(lst_sorted);
	return (1);
}

/*Verifica que una lista de numeros sea correcta y no contenga errores*/
int	check_error(t_list *lst)
{
	if (check_duplicate(lst) == -1)
		return (-1);
	else
		return (1);
}
