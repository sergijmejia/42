/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:07:20 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/11 18:48:10 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

/* ************************************************************************** */
/* *************************  FUNCIONES AUXILIARES  ************************* */
/* ************************************************************************** */

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

/*Devuelve el malor maximo de la lista*/
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
static t_list   *ft_lstdup(t_list *lst)
{
        t_list  *new_lst;
        int     len;

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

/*Imprime por pantalla la lista lst*/
static void     print_lst(t_list *lst)
{
	if (lst == NULL)
                return ;
        ft_printf("%d ", *(int *)(lst->content));
        if (lst->next == NULL)
                return ;
        else
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
static void     swap(t_list **lst)
{
        t_list  *aux;

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
static void     rotate_rotate(t_list **lst_a, t_list **lst_b)
{
	rotate(lst_a);
	rotate(lst_b);
	return ;
}

/*Desplaza hacia abajo todos los elementos de la lista lst*/
static void	reverse_rotate(t_list **lst)
{
	t_list  *aux;

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

/*Cuenta cuantos movimientos se han de hacer en lst para organizar correctamente x habiendo desplazado moves posiciones previamente*/
static int	count_moves_b(t_list *lst, int x, int moves)
{
	int		size;
	int		i;
	int		j;
	int		boolean;
	int		aux_1;
	int		aux_2;
	static int	min;
	static int	max;
	t_list	*aux;

	size = ft_lstsize(lst);
	min = ft_lstmin(lst);
	max = ft_lstmax(lst);
	ft_printf("La longitud de la lista es: %d\n", size);

	i = 0;
	boolean = 0;
	if (x < min || x > max)
	{
		aux = lst;
		while (!boolean)
		{
			i++;
			ft_printf("\nMovimiento #%d. ", i);
			aux_2 = *(int *)((aux->next)->content);
			if (aux_2 == max)
				break ;
			aux = aux->next;
		}
	}
	else if (!(*(int *)(lst->content) < x) || !(x < *(int *)(ft_lstlast(lst)->content)))
	{
		aux = lst;
		while (!boolean)
		{
			i++;
			ft_printf("\nMovimiento #%d. ", i);
			aux_1 = *(int *)(aux->content);
			if (aux->next)
				aux_2 = *(int *)((aux->next)->content);
			else
				aux_2 = *(int *)(lst->content);
			ft_printf("aux_1 = %d ; aux_2 = %d\n", aux_1, aux_2);
			if (x < aux_1 && x > aux_2)
				break ;
			aux = aux->next;
		}
	}
	i = (i + moves) % size;
	ft_printf("En total hace %d movimientos hacia abajo\n", i);
	j = size - i;
	ft_printf("Esto equivale a hacer %d movimientos hacia arriba\n", j);
	if (i >= j)
		return (j);
	else
		return ((-1) * i);

}

/*Realiza los movimientos con los datos transferidos*/
static void	do_moves(t_list **a, t_list **b, int pos, int direction, int rotate)
{
	int	size_a;
	int	size_b;
	int	moves_a;
	int	moves_b;

	size_a = ft_lstsize(*a);
	size_b = ft_lstsize(*b);
	if (direction_a == -1 && rotate == 0)
	{
		if (pos > 0)
			ft_printf("Exec");
		while (pos > 0)
		{
			rotate(a);
			pos--;
			ft_printf(" ra");
		}
	}
	if (direction_a == -1 && rotate == 1)
	{
		if (pos > 0)
			ft_printf("Exec");
		while (pos > 0)
		{
			rotate_rotate(a, b);
			pos--;
			ft_printf(" rr");
		}
	}
	if (direction_a == 1 && rotate == 0)
	{
		if (pos > 0)
			ft_printf("Exec");
		while (size_a - pos > 0)
		{
			reverse_rotate(a);
			pos++;
			ft_printf(" rra");
		}
	}
	if (direction_a == 1 && rotate == 1)
	{
		if (pos > 0)
			ft_printf("Exec");
		while (size_a - pos > 0)
		{
			reverse_rotate_rotate(a, b);
			pos++;
			ft_printf(" rrr");
		}
	}
	moves_b = count_moves_b(*b, *(int *)((*b)->content), 0);


}

/*Cuenta los movimientos necesarios para pasar un elento de la lista a a la lista b. Se calcula con el elemento que requiera menor cantidad de movimientos*/
static int min_move (t_list **a, t_list **b)
{
	int	i;
	int	moves;
	int	moves_a;
	int	moves_b;
	int	moves_b_dir;
	int	moves_i_neg;
	int	aux;
	int	pos;
	int	direction_a;
	int	direction_b;
	int	rotate;
	int	num_b;

	pos = 0;
	direction_a = -1;
	direction_b = 1;
	rotate = 0;
	num_b = *(int *)((*a)->content);
	moves = count_moves_b(*b, num_b, 0);
	ft_printf("Para pasar el elemento en pos %d necesita %d movimientos.\n", pos, moves);
	i = 1;
	while (i < moves)
	{
		moves_a = count_moves_a(*a, i, -1);
		num_b = *(int *)(ft_lstpos(*a, i)->content);
		//ft_printf("Para la primera se analiza los movimientos para ")
		moves_b_dir = count_moves_b(*b, num_b, (-1) * moves_a);
		moves_b = ft_abs(moves_b_dir);
		if ((moves_a + moves_b) < moves)
		{
			pos = i;
			direction_a = -1;
			rotate = 1;
			moves = moves_a + moves_b;
			if (moves_b_dir < 0)
				direction_b = -1;
			else
				direction_b = 1;
		}
		moves_b_dir = count_moves_b(*b, num_b, 0);
		moves_b = ft_abs(moves_b_dir);
		if ((moves_a + moves_b) < moves)
		{
			pos = i;
			direction_a = -1;
			rotate = 0;
			moves = moves_a + moves_b;
			if (moves_b_dir < 0)
				direction_b = -1;
			else
				direction_b = 1;
		}
		if (moves >= 3)
		{
			moves_a = count_moves_a(*a, moves - 2, 1);
			num_b = *(int *)(ft_lstpos(*a, moves - 2)->content);
			moves_b_dir = count_moves_b(*b, num_b, moves_a);
			moves_b = ft_abs(moves_b_dir);
			if ((moves_a + moves_b) < moves)
			{
				pos = moves - 2;
				direction_a = 1;
				rotate = 1;
				moves = moves_a + moves_b;
				if (moves_b_dir < 0)
					direction_b = -1;
				else
					direction_b = 1;
			}
		}
		if (moves >= 3)
		{
			moves_b_dir = count_moves_a(*b, num_b, 0);
			moves_b = ft_abs(moves_b_dir);
			if ((moves_a + moves_b) < moves)
			{
				pos = moves - 2;
				direction_a = 1;
				rotate = 0;
				moves = moves_a + moves_b;
				if (moves_b_dir < 0)
					direction_b = -1;
				else
					direction_b = 1;
			}
		}
		ft_printf("Para pasar el elemento en pos %d necesita %d movimientos.\n", pos, moves + 1);
		i++;
	}
	do_moves(a, b, pos, direction_a, direction_b, rotate);
	moves++;
	ft_printf("El elemento que menos movimientos necesita es: %d. Se pasa a la lista B en %d movimientos", *(int *)(ft_lstpos(*a, pos)->content), moves);
	return (moves);
}

/* ************************************************************************** */
/* **************************  FUNCION  PUSH_SWAP  ************************** */
/* ************************************************************************** */

static int     push_swap(t_list **a, t_list **b)
{
	//*lst->content es el numero en la posicion 1
	////*lst->next apunta al siguiente elemento

	int	moves;
	int	min;
	int	max;

	print_ab_lists(*a, *b);
	
	ft_printf("\n");
	min = *(int *)((*a)->content);
	max = *(int *)((*a)->content);
	push(b, a);
	push(b, a);
	ft_printf("Exec pb pb:\n");
	print_ab_lists(*a, *b);
	moves = min_move(a, b);
	ft_printf("\n");
	ft_printf("%d\n", moves);
	return (1);
}

int     main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	t_list *new_node;
	int		i;
	int		*new_num;

	i = 1;
	a = NULL;
	b = NULL;
	while (i < argc)
	{
		new_num = (int *) malloc (sizeof(int));
		new_num[0] =  ft_atoi(argv[i]);
		new_node = ft_lstnew(new_num);
		ft_lstadd_back(&a, new_node);
		i++;
	}
	push_swap(&a, &b);
	ft_lstclear(&a, free);
	return (0);
}
