/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:07:20 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/21 14:01:36 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ************************************************************************** */
/* *************************  FUNCIONES AUXILIARES  ************************* */
/* ************************************************************************** */

/*Funcion para limpiar listas*/
static t_list	*ft_free_lst(t_list **lst)
{
	ft_lstclear(lst, free);
	return (*lst);
}

/*Verifica que la lista de enteros de entrada no contiene caracteres no admitidos*/
static int	check_error(char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str) && !(*str >= '\t' && *str <= '\r'))
		{
			if (*str != '+' && *str != '-' && *str != ' ')
			{
				ft_printf("Error\n");
				return (0);
			}
		}
		str++;
	}
	return (1);
}

/*Crea la lista de enteros lst a partir del string str*/
static t_list	*create_list(t_list **lst, char *str)
{
	int		*new_num;
	t_list	*new_node;

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
		while (*str >= '\t' && *str <= '\r')
			str++;
		while (*str == '-' || *str == '+' || *str == ' ')
			str++;
		while (*str >= '0' && *str <= '9')
			str++;
	}
	return (*lst);
}

/*Devuelve el valor minimo de la lista*/
static int	ft_lstmin(t_list *lst)
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
static int	ft_lstmax(t_list *lst)
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

/*Devuelve un puntero a la posicion x de la lista lst*/
static t_list	*ft_lstpos(t_list *lst, int x)
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
static t_list	*ft_lstsecondlast(t_list *lst)
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
static t_list	*ft_lstdup(t_list *lst)
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
static void	print_lst(t_list *lst)
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
static void	print_ab_lists(t_list *a, t_list *b)
{
	ft_printf("Lista a: ");
	print_lst(a);
	ft_printf("\nLista b: ");
	print_lst(b);
	ft_printf("\n");
}

/* ************************************************************************** */
/* *****************  FUNCIONES DE MOVIMIENTO DE PUSH_SWAP  ***************** */
/* ************************************************************************** */

/*Intercambia las dos primeras posiciones de la lista lst*/
static void	swap(t_list **lst)
{
	t_list	*aux;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	aux = (*lst)->next;
	(*lst)->next = aux->next;
	aux->next = *lst;
	*lst = aux;
	return ;
}

/*Intercambia las dos primeras posiciones en la lista lst_a y en la lista lst_b a la vez*/
static void	swap_swap(t_list **lst_a, t_list **lst_b)
{
	swap(lst_a);
	swap(lst_b);
	return ;
}

/*Toma el primer elemento de la lista lst_b y lo pone el primero en la lista lst_a*/
static void	push(t_list **lst_a, t_list **lst_b)
{
	t_list	*aux;

	if (*lst_b == NULL)
		return ;
	aux = (*lst_b)->next;
	(*lst_b)->next = (*lst_a);
	*lst_a = *lst_b;
	*lst_b = aux;
	return ;
}

/*Desplaza hacia arriba todos los elementos del la lista lst*/
static void	rotate(t_list **lst)
{
	t_list	*aux;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	aux = *lst;
	*lst = (*lst)->next;
	aux->next = NULL;
	ft_lstadd_back(lst, aux);
	return ;
}

/*Desplaza hacia arriba todos los elementos de la lista lst_a y la lista lst_b a la vez*/
static void	rotate_rotate(t_list **lst_a, t_list **lst_b)
{
	rotate(lst_a);
	rotate(lst_b);
	return ;
}

/*Desplaza hacia abajo todos los elementos de la lista lst*/
static void	reverse_rotate(t_list **lst)
{
	t_list	*aux;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	aux = ft_lstlast(*lst);
	(ft_lstsecondlast(*lst))->next = NULL;
	ft_lstadd_front(lst, aux);
	return ;
}

/*Desplaza hacia abajo todos los elementos de la lista lst_a y la lista lst_b a la vez*/
static void	reverse_rotate_rotate(t_list **lst_a, t_list **lst_b)
{
	reverse_rotate(lst_a);
	reverse_rotate(lst_b);
	return ;
}

/* ************************************************************************** */
/* *******************  FUNCIONES ALGORITMO ORGANIZACION  ******************* */
/* ************************************************************************** */

/*Cuenta la cantidad de movimientos que se han de hacer para llevar la posicion x hasta la primera posicion siguiendo una determinada direccion dir*/
static int	count_moves_a(t_list *lst, int pos, int dir)
{
	int	size;

	if (lst == NULL)
		return (0);
	size = ft_lstsize(lst);
	if (pos == 0 || dir == -1)
		return (pos);
	else
		return (size - pos);
}

/*Devuelve la cantidad de movimientos necesarios en lst hasta max*/
static int	moves_to_max(t_list *lst)
{
	t_list	*pnt;
	int		moves;
	int		boolean;
	int		max;

	moves = 0;
	boolean = 1;
	max = ft_lstmax(lst);
	pnt = lst;
	while (boolean)
	{
		if ((*(int *)(pnt->content)) == max)
			break ;
		pnt = pnt->next;
		moves++;
	}
	return (moves);
}

/*Devuelve la cantidad de movimientos necesarios para unicar crrectamente x en la lista lst*/
static int	moves_to_x(t_list *lst, int x)
{
	int		x_1;
	int		x_2;
	int		moves;
	int		boolean;
	t_list	*pnt;

	pnt = lst;
	boolean = 1;
	moves = 0;
	while (boolean)
	{
		moves++;
		x_1 = *(int *)(pnt->content);
		if (pnt->next)
			x_2 = *(int *)((pnt->next)->content);
		else
			x_2 = *(int *)(lst->content);
		if (x <= x_1 && x >= x_2)
			break ;
		pnt = pnt->next;
	}
	return (moves);
}

/*Cuenta cuantos movimientos se han de hacer en lst para organizar correctamente x habiendo desplazado moves posiciones previamente*/
static int	count_moves_b(t_list *lst, int x, int moves)
{
	int		size;
	int		i;
	int		j;
	int		min;
	int		max;

	size = ft_lstsize(lst);
	min = ft_lstmin(lst);
	max = ft_lstmax(lst);
	i = 0;
	if (x < min || x > max)
		i = moves_to_max(lst);
	else if (!(*(int *)(lst->content) < x) || !(x < *(int *)(ft_lstlast(lst)->content)))
		i = moves_to_x(lst, x);
	i = (i + moves) % size;
	j = size - i;
	if (i >= j)
		return (j);
	else
		return ((-1) * i);
}

/*Realiza los movimientos de la lista a en direccion negativa*/
static void	move_a_neg(t_list **a, t_list **b, int pos, int rot)
{
	while (pos > 0)
	{
		pos--;
		if (rot == 0)
		{
			rotate(a);
			ft_printf("ra\n");
		}
		else
		{
			rotate_rotate(a, b);
			ft_printf("rr\n");
		}
	}
}

/*Realiza los movimientos de la lista a en direccion positiva*/
static void	move_a_pos(t_list **a, t_list **b, int pos, int rot)
{
	int	size;

	size = ft_lstsize(*a);
	while (size - pos > 0)
	{
		pos++;
		if (rot == 0)
		{
			reverse_rotate(a);
			ft_printf("rra\n");
		}
		else
		{
			reverse_rotate_rotate(a, b);
			ft_printf("rrr\n");
		}
	}
}

/*Realiza los movimientos de la lista b*/
static void	move_b(t_list **a, t_list **b, int direction)
{
	int	moves;

	moves = ft_abs(count_moves_b(*b, *(int *)((*a)->content), 0));
	while (moves > 0)
	{
		if (direction == 1)
		{
			reverse_rotate(b);
			ft_printf("rrb\n");
		}
		else
		{
			rotate(b);
			ft_printf("rb\n");
		}
		moves--;
	}
}

/*Realiza los movimientos de a con los datos transferidos*/
static void	do_moves_a(t_list **a, t_list **b, t_mov_properties new_mov)
{
	int	size_a;

	size_a = ft_lstsize(*a);
	if (new_mov.dir_a == -1)
		move_a_neg(a, b, new_mov.pos, new_mov.rotate);
	if (new_mov.dir_a == 1)
		move_a_pos(a, b, new_mov.pos, new_mov.rotate);
}

/*Realiza los movimientos de b con los datos transferidos*/
static void	do_moves_b(t_list **a, t_list **b, t_mov_properties new_mov)
{
	move_b(a, b, new_mov.dir_b);
	ft_printf("pb\n");
	push(b, a);
}

/*Reuccion de la funcion min_move*/

static int	rotate_definition(t_list **a, t_list **b, int moves, int i)
{
	int	moves_a;
	int	moves_b;
	int	num_b;
	int	rotate;

	moves_a = count_moves_a(*a, i, -1);
	num_b = *(int *)(ft_lstpos(*a, i)->content);
	moves_b = ft_abs(count_moves_b(*b, num_b, (-1) * moves_a));
	if ((moves_a + moves_b) < moves)
		rotate = 1;
	moves_b = ft_abs(count_moves_b(*b, num_b, 0));
	if ((moves_a + moves_b) < moves)
		rotate = 0;
	return (rotate);
}

/*Asigna el valor a direction_b*/
static int	set_direction_b(int moves_dir)
{
	if (moves_dir < 0)
		return (-1);
	else
		return (1);
}

/*Modifica el valor de moves, direction_b y result en caso de haber obtenido un move menor*/
static int	set_result(t_mov_properties *new_mov, int i)
{
	new_mov->mov_b = ft_abs(new_mov->mov_b_dir);
	new_mov->mov = new_mov->mov_a + new_mov->mov_b;
	new_mov->dir_b = set_direction_b(new_mov->mov_b_dir);
	return (i);
}

/*Calcula la minima combinacion de move_a y move_b*/
static int	min_move_ab(t_list **a, t_list **b, int i, t_mov_properties *new_mov)
{
	int	num_b;
	int	result;

	if (i == 0)
		return (-1);
	result = 0;
	new_mov->mov_a = count_moves_a(*a, i, -1);
	num_b = *(int *)(ft_lstpos(*a, i)->content);
	new_mov->mov_b_dir = count_moves_b(*b, num_b, (-1) * new_mov->mov_a);
	if ((new_mov->mov_a) + ft_abs(new_mov->mov_b_dir) < (new_mov->mov))
		result = set_result(new_mov, 1);
	new_mov->mov_b_dir = count_moves_b(*b, num_b, 0);
	if ((new_mov->mov_a) + ft_abs(new_mov->mov_b_dir) < (new_mov->mov))
		result = set_result(new_mov, 2);
	new_mov->mov_a = count_moves_a(*a, ft_lstsize(*a) - i, 1);
	num_b = *(int *)(ft_lstpos(*a, ft_lstsize(*a) - i)->content);
	new_mov->mov_b_dir = count_moves_b(*b, num_b, new_mov->mov_a);
	if ((new_mov->mov_a) + ft_abs(new_mov->mov_b_dir) < (new_mov->mov))
		result = set_result(new_mov, 3);
	new_mov->mov_b_dir = count_moves_b(*b, num_b, 0);
	if ((new_mov->mov_a) + ft_abs(new_mov->mov_b_dir) < (new_mov->mov))
		result = set_result(new_mov, 4);
	return (result);
}

/*Asigna valor a direction_a*/
static int	set_direction_a(int old_direction_a, int result)
{
	if (result == 0)
		return (old_direction_a);
	if (result == -1 || result == 1 || result == 2)
		return (-1);
	else
		return (1);
}

/*Asigna el valor a rotate*/
static int	set_rotate(int old_rotate, int result)
{
	if (result == 0)
		return (old_rotate);
	if (result == -1 || result == 2 || result == 4)
		return (0);
	else
		return (1);
}

/*Asigna el valor a pos*/
static int	set_pos(t_list **a, int old_pos, int result, int i)
{
	if (result == -1)
		return (0);
	if (result == 0)
		return (old_pos);
	if (result == 1 | result == 2)
		return (i);
	else
		return (ft_lstsize(*a) - i);
}

/*Cuenta los movimientos necesarios para pasar un elento de la lista a a la lista b. Se calcula con el elemento que requiera menor cantidad de movimientos*/
static void	min_move(t_list **a, t_list **b)
{
	int					i;
	int					option;
	t_mov_properties	new_mov;

	if ((count_moves_b(*b, (*(int *)((*a)->content)), 0)) < 0)
		new_mov.dir_b = -1;
	else
		new_mov.dir_b = 1;
	new_mov.pos = 0;
	new_mov.mov = ft_abs(count_moves_b(*b, (*(int *)((*a)->content)), 0));
	i = 0;
	while ((i < new_mov.mov && i < ft_lstsize(*a)) || new_mov.mov == 0)
	{
		option = min_move_ab(a, b, i, &new_mov);
		new_mov.pos = set_pos(a, new_mov.pos, option, i);
		new_mov.dir_a = set_direction_a(new_mov.dir_a, option);
		new_mov.rotate = set_rotate(new_mov.rotate, option);
		if (i >= (ft_lstsize(*a) / 2))
			break ;
		i++;
	}
	do_moves_a(a, b, new_mov);
	do_moves_b(a, b, new_mov);
}

/*Funcion que calcula los movimientos y la direccion para tener max arriba de la lista*/
/*CUANDO SE SEPAREN LOS ARCHIVOS CAMBIAR NOMBRE A MOVES_TO_MAX*/
static int	moves_to_max_b(t_list *lst, int max, int size, t_mov_properties *new_mov)
{
	int	i;

	new_mov->dir_b = -1;
	i = 0;
	while ((*(int *)(lst->content)) != max)
	{
		i++;
		lst = lst->next;
	}
	if ((size - i) < i)
	{
		i = size - i;
		new_mov->dir_b = 1;
	}
	return (i);
}

/*Funcion que devuelve la lista b organizada con el max arriba y en la menor cantidad de mov posibles*/
static void	organize_b(t_list **lst, int size)
{
	int					max;
	int					i;
	t_mov_properties	new_mov;

	max = ft_lstmax(*lst);
	i = moves_to_max_b(*lst, max, size, &new_mov);
	while (i > 0)
	{
		if (new_mov.dir_b == 1)
		{
			reverse_rotate(lst);
			ft_printf("rrb\n");
		}
		if (new_mov.dir_b == -1)
		{
			rotate(lst);
			ft_printf("rb\n");
		}
		i--;
	}
}

/*Funcion que devuelve la lista a organizada con el min arriba y en la menor cantidad de mov posibles*/
static void	organize_a(t_list **a, t_list **b, int size_b)
{
	int	b_first;
	int	a_last;
	int	a_second_last;

	while (size_b > 0)
	{
		b_first = *(int *)((*b)->content);
		a_last = *(int *)((ft_lstlast(*a))->content);
		a_second_last = *(int *)((ft_lstsecondlast(*a))->content);
		if (b_first > a_last || (b_first < a_last && b_first < a_second_last && a_second_last != ft_lstmax(*a)))
		{
			push(a, b);
			ft_printf("pa");
		}
		else
		{
			reverse_rotate(a);
			ft_printf("rra");
		}
		if (size_b != 1)
			ft_printf("\n");
		size_b = ft_lstsize(*b);
	}
}

/*Funcion que traspasa todos los numeros de la lista b a la lista a (que aun tiene 2 elementos)*/
static void	organize(t_list **a, t_list **b)
{
	int	size_b;
	int	b_first;
	int	a_last;
	int	a_second_last;

	size_b = ft_lstsize(*b);
	organize_b(b, size_b);
	organize_a(a, b, size_b);
}

/* ************************************************************************** */
/* **************************  FUNCION  PUSH_SWAP  ************************** */
/* ************************************************************************** */
static int	push_swap(t_list **a, t_list **b)
{
	int	size;

	push(b, a);
	push(b, a);
	ft_printf("pb\n");
	ft_printf("pb\n");
	size = ft_lstsize(*a);
	while (size > 2)
	{
		min_move(a, b);
		size = ft_lstsize(*a);
	}
	if ((*(int *)((*a)->content)) > (*(int *)(((*a)->next)->content)))
	{
		swap(a);
		ft_printf("sa\n");
	}
	organize(a, b);
	return (1);
}

/*Programa main principal*/
int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	char	*str;

	if (argc != 2)
		return (1);
	a = NULL;
	b = NULL;
	str = argv[1];
	if (!check_error(str))
		return (1);
	create_list(&a, str);
	if (!a)
	{
		ft_printf("Error\n");
		return (1);
	}
	push_swap(&a, &b);
	ft_printf("\n");
	ft_lstclear(&a, free);
	return (0);
}
