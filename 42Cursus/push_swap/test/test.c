/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:07:20 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/09 16:41:01 by smejia-a         ###   ########.fr       */
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
	ft_printf("\nLista b:");
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

/*Cuenta cuantos movimientos se han de hacer en lst para organizar correctamente x*/
static int	count_move(t_list *lst, int x)
{
	int		size;
	int		i;
	int		j;
	int		boolean;
	int		aux_1;
	int		aux_2;
	t_list	*aux;

	size = ft_lstsize(lst);
	i = 0;
	boolean = 0;
	if (*(int *)(lst->content) < x && lst->content > ft_lstlast(lst)->content)
		return (i);
	aux = lst;
	while (!boolean)
	{
		i++;
		aux_1 = aux->content;
		aux_2 = (ft_lstlast(aux))->content;
		if (x < aux_1 && x > aux_2)
			break ;
		aux = aux->next;
	}
	j = len - i;
	if (i >= j)
		return (j);
	else
		return (i);

}

/* ************************************************************************** */
/* **************************  FUNCION  PUSH_SWAP  ************************** */
/* ************************************************************************** */

static int     push_swap(t_list **a)
{
	//*lst->content es el numero en la posicion 1
	////*lst->next apunta al siguiente elemento

	int             len;
	int             result;
	int		x;
	t_list        *b;
	t_list  *lst;

	x =17;
        result = count_move(*a, x);
	ft_printf("%d\n", result);
	b = NULL;
	print_ab_lists(*a, b);
	swap(a);
	ft_printf("sa\n");
	print_ab_lists(*a, b);
	rotate(a);
	ft_printf("ra\n");
	print_ab_lists(*a, b);
	push(&b, a);
	ft_printf("pb\n");
	print_ab_lists(*a, b);
	reverse_rotate(a);
	ft_printf("rra\n");
	print_ab_lists(*a, b);
	reverse_rotate(a);
	ft_printf("rra\n");
	print_ab_lists(*a, b);
	push(&b, a);
	ft_printf("pb\n");
	print_ab_lists(*a, b);
	reverse_rotate_rotate(a, &b);
	ft_printf("rrr\n");
	print_ab_lists(*a, b);
	push(a, &b);
	ft_printf("pa\n");
	print_ab_lists(*a, b);
	reverse_rotate_rotate(a, &b);
	ft_printf("rrr\n");
	print_ab_lists(*a, b);
	return (1);
}

int     main()
{
        t_list	*a;
        t_list  *num1;
        t_list  *num2;
        t_list  *num3;
        t_list  *num4;
	t_list	*num5;
        int	*n0;
	int     *n1;
        int     *n2;
        int     *n3;
        int     *n4;
	int	*n5;
	int	*n6;
	int	*n7;
	int	*n8;
	int	*n9;
	int	*n10;
	int	*n11;
	int	*n12;

	n0 = (int *) malloc (sizeof(int));
	n0[0] = 9;
	n1 = (int *) malloc (sizeof(int));
        n1[0] = 8;
	n2 = (int *) malloc (sizeof(int));
        n2[0] = 6;
	n3 = (int *) malloc (sizeof(int));
        n3[0] = 3;
	n4 = (int *) malloc (sizeof(int));
        n4[0] = 35;
	n5 = (int *) malloc (sizeof(int));
	n5[0] = 33;
	n6 = (int *) malloc (sizeof(int));
	n6[0] = 31;
	n7 = (int *) malloc (sizeof(int));
	n7[0] = 23;
	n8 = (int *) malloc (sizeof(int));
	n8[0] = 22;
	n9 = (int *) malloc (sizeof(int));
	n9[0] = 18;
	n10 = (int *) malloc (sizeof(int));
	n10[0] = 16;
	n11 = (int *) malloc (sizeof(int));
	n11[0] = 12;
	num0 = ft_lstnew(n0);
        num1 = ft_lstnew(n1);
        num2 = ft_lstnew(n2);
        num3 = ft_lstnew(n3);
        num4 = ft_lstnew(n4);
	num5 = ft_lstnew(n5);
	num6 = ft_lstnew(n6);
	num7 = ft_lstnew(n7);
	num8 = ft_lstnew(n8);
	num9 = ft_lstnew(n9);
	num10 = ft_lstnew(n10);
	num11 = ft_lstnew(n11);

        a = num0;
	ft_lstadd_back(&a, num1);
        ft_lstadd_back(&a, num2);
        ft_lstadd_back(&a, num3);
        ft_lstadd_back(&a, num4);
	ft_lstadd_back(&a, num5);
	ft_lstadd_back(&a, num6);
	ft_lstadd_back(&a, num7);
	ft_lstadd_back(&a, num8);
	ft_lstadd_back(&a, num9);
	ft_lstadd_back(&a, num10);
	ft_lstadd_back(&a, num11);
        push_swap(&a);
        ft_lstclear(&a, free);
        return (0);
}

