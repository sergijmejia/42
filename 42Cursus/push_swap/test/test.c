/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:07:20 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/10 14:18:59 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

/* ************************************************************************** */
/* *************************  FUNCIONES AUXILIARES  ************************* */
/* ************************************************************************** */

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

/*Cuenta cuantos movimientos se han de hacer en lst para organizar correctamente x habiendo desplazado i posiciones previamente*/
static int	count_moves_b(t_list *lst, int x, int i)
{
	int		size;
	int		j;
	int		boolean;
	int		aux_1;
	int		aux_2;
	t_list	*aux;

	size = ft_lstsize(lst);
	ft_printf("La longitud de la lista es: %d\n", size);
	i = 0;
	boolean = 0;
	if (*(int *)(lst->content) < x && lst->content > ft_lstlast(lst)->content)
		return (i);
	aux = lst;
	while (!boolean)
	{
		i++;
		ft_printf("\nMovimiento #%d. ", i);
		aux_1 = *(int *)(aux->content);
		aux_2 = *(int *)((aux->next)->content);
		ft_printf("aux_1 = %d ; aux_2 = %d\n", aux_1, aux_2);
		if (x < aux_1 && x > aux_2)
			break ;
		aux = aux->next;
	}
	ft_printf("En total hace %d movimientos hacia abajo\n", i);
	j = size - i;
	ft_printf("Esto equivale a hacer %d movimientos hacia arriba\n", j);
	if (i >= j)
		return (j);
	else
		return (i);

}

static int min_move (t_list **a, t_list **b)
{
	int	i;
	int	moves;
	int	aux;
	int	moves_aux;
	int	pos;
	int	direction;

	i = 0;
	pos = 0;
	direction = -1;
	mix_move = 1;
	moves_a = count_moves_a(*a, i, direction);
	moves_b = count_moves_b(*b, *a[pos], (-1) * (moves_a));
	moves = moves_a + moves_b;

	
	
		


}

/* ************************************************************************** */
/* **************************  FUNCION  PUSH_SWAP  ************************** */
/* ************************************************************************** */

static int     push_swap(t_list **a)
{
	//*lst->content es el numero en la posicion 1
	////*lst->next apunta al siguiente elemento

	int             size;
	int             result;
	int		mov;
	int		i;
	t_list        *b;
	t_list  *lst;

	b = NULL;
	print_ab_lists(*a, b);
	ft_printf("\n");
	push(&b, a);
	ft_printf("pb\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	push(&b, a);
	ft_printf("pb\n");
	print_ab_lists(*a, b);

	size = ft_lstsize(*a);
	i = 1;
	while (size > 0)
	{
		min_move(a, &b);
		size = ft_lstsize(*a);
	}
	ft_printf("\n");
	swap(a);
	ft_printf("sa\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	rotate(a);
	ft_printf("ra\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	push(&b, a);
	ft_printf("pb\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	reverse_rotate(a);
	ft_printf("rra\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	reverse_rotate(a);
	ft_printf("rra\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	push(&b, a);
	ft_printf("pb\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	reverse_rotate_rotate(a, &b);
	ft_printf("rrr\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	push(a, &b);
	ft_printf("pa\n");
	print_ab_lists(*a, b);
	ft_printf("\n");
	reverse_rotate_rotate(a, &b);
	ft_printf("rrr\n");
	print_ab_lists(*a, b);
	for (int j = 0; j < 4; j++)
	{
		ft_printf("\n");
		rotate(a);
		ft_printf("ra\n");
		print_ab_lists(*a, b);
		if (j % 2 == 1)
		{
			ft_printf("\n");
			push(&b, a);
			ft_printf("pb\n");
			print_ab_lists(*a, b);
		}
	}
	for (int j = 0; j < 3; j++)
	{
		ft_printf("\n");
		rotate(a);
		ft_printf("ra\n");
		print_ab_lists(*a, b);
	}
	lst = *a;
	*a = b;
	b = lst;
	ft_printf("\n");
	print_ab_lists(*a, b);
	result = count_moves_a(*a, 2, 1) + count_moves_b(b, 12, 0);
	ft_printf("\n");
	ft_printf("%d\n", result);
	return (1);
}

int     main(int argc, char **argv)
{
	t_list	*a;
	t_list *new_node;
	int		i;
	int		*new_num;

	i = 1;
	a = NULL;
	while (i < argc)
	{
		new_num = (int *) malloc (sizeof(int));
		new_num[0] =  ft_atoi(argv[i]);
		new_node = ft_lstnew(new_num);
		ft_lstadd_back(&a, new_node);
		i++;
	}
	push_swap(&a);
	ft_lstclear(&a, free);
	return (0);
}
