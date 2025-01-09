/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:13:57 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/09 12:33:37 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Funcion que libera la memoria de las listas a y b*/
static int	ft_ab_lst_free(t_list **a, t_list **b)
{
	ft_lstclear(a, free);
	ft_lstclear(b, free);
	return (0);
}

/*Funcion que vacia la lista lst e imprime "Error" por el fd 2*/
static int	ft_error(t_list **a, t_list **b)
{
	ft_ab_lst_free(a, b);
	write(2, "Error\n", 6);
	return (1);
}

/*Funcion que verifica que las ordenes de push_swap existan*/
static int	check_test_push_swap(t_list **a, t_list **b)
{
	char	*str;
	size_t	size;

	str = get_next_line(0);
	while (str != NULL)
	{
		size = ft_strlen(str);
		if (size == 3)
		{
			if (functions_two_len(a, b, str) == -1)
				return (-1);
		}
		else if (size == 4)
		{
			if (functions_three_len(a, b, str) == -1)
				return (-1);
		}
		else
			return (-1);
		str = get_next_line(0);
	}
	return (1);
}

/*Funcion principal de verificacion de push_swap*/
int	check_push_swap(t_list **a, t_list **b)
{
	int	text;

	text = check_test_push_swap(a, b);
	if (text == -1)
		return (-1);
	if (ft_lstsize(*b) != 0 || !(organized_lst(*a)))
		ft_ko(a, b);
	else
		ft_ok(a, b);
	return (1);
}

/*Programa main principal*/
int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	char	*str;
	int		i;

	a = NULL;
	b = NULL;
	i = 1;
	if (argc < 2)
		return (1);
	while (i < argc)
	{
		str = argv[i];
		if (!check_error_str(str))
			return (ft_error(&a, &b));
		create_list(&a, str);
		if (!a)
			return (ft_error(&a, &b));
		i++;
	}
	if (check_error_lst(a) == -1)
		return (ft_error(&a, &b));
	if (check_push_swap(&a, &b) == -1)
		return (ft_error(&a, &b));
	return (ft_ab_lst_free(&a, &b));
}
