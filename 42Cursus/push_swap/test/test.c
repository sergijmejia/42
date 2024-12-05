#include "libft.h"

/*********FUNCIONES DE MOVIMIENTO DE PUSH_SWAP*********/

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

/*Desplaza hacia arriba todos los elementos del list*/
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
        /*int     n1;
        int     n2;
        int     n3;
        int     n4;*/


	
	if (lst == NULL)
                return ;
	/*n1 = *(int *)((lst)->content);
        n2 = *(int *)((lst->next)->content);
        n3 = *(int *)(((lst->next)->next)->content);
        n4 = *(int *)((((lst->next)->next)->next)->content);*/

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

static int     push_swap(t_list **a)
{
	//*lst->content es el numero en la posicion 1
	////*lst->next apunta al siguiente elemento

	int             len;
	int             result;
	t_list        *b;
	t_list  *lst;

        result = 0;
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
        int     *n1;
        int     *n2;
        int     *n3;
        int     *n4;
	int	*n5;

	n1 = (int *) malloc (sizeof(int));
        n1[0] = 23;
	n2 = (int *) malloc (sizeof(int));
        n2[0] = 72;
	n3 = (int *) malloc (sizeof(int));
        n3[0] = 44;
	n4 = (int *) malloc (sizeof(int));
        n4[0] = 2;
	n5 = (int *) malloc (sizeof(int));
	n5[0] = 13;
        num1 = ft_lstnew(n1);
        num2 = ft_lstnew(n2);
        num3 = ft_lstnew(n3);
        num4 = ft_lstnew(n4);
	num5 = ft_lstnew(n5);
        a = num1;
        ft_lstadd_back(&a, num2);
        ft_lstadd_back(&a, num3);
        ft_lstadd_back(&a, num4);
	ft_lstadd_back(&a, num5);
        push_swap(&a);
        ft_lstclear(&a, free);
        return (0);
}

