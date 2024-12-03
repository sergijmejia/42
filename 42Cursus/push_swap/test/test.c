#include "libft.h"

/*Funciones de movimiento del push swap*/

static void     swap(t_list **lst)
{
        t_list  *aux1;
        t_list  *aux2;

        if (*lst == NULL || (*lst)->next == NULL)
                return ;
        aux1 = *lst;
        aux2 = (*lst)->next;
        aux1 = aux2->next;
        aux2->next = aux1;
        *lst = aux2;
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
        int     n1;
        int     n2;
        int     n3;
        int     n4;


	
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

static int     push_swap(t_list **a)
{
        //*lst->content es el numero en la posicion 1
        //*lst->next apunta al siguiente elemento

        int             len;
        int             result;
        //t_list        *b;
        t_list  *lst;
	int	n1;
	int	n2;
	int	n3;
	int	n4;

        result = 0;
	n1 = *(int *)((*a)->content);
	n2 = *(int *)(((*a)->next)->content);
	n3 = *(int *)((((*a)->next)->next)->content);
	n4 = *(int *)(((((*a)->next)->next)->next)->content);
        len = ft_lstsize(*a);
        lst = ft_lstdup(*a);
        if(lst == NULL)
                return (0); //ESTO SE DEBE REVISAR
        print_lst(*a);
        ft_printf("\n");
        print_lst(lst);
        ft_printf("\n");
        swap(&lst);
	n1 = *(int *)((lst)->content);
        n2 = *(int *)((lst->next)->content);
        n3 = *(int *)(((lst->next)->next)->content);
        n4 = *(int *)((((lst->next)->next)->next)->content);
        print_lst(lst);
        return (1);
}

int     main()
{
        t_list	*a;
        t_list  *num1;
        t_list  *num2;
        t_list  *num3;
        t_list  *num4;
        int     n1;
        int     n2;
        int     n3;
        int     n4;

        n1 = 23;
        n2 = 72;
        n3 = 44;
        n4 = 2;
        num1 = ft_lstnew(&n1);
        num2 = ft_lstnew(&n2);
        num3 = ft_lstnew(&n3);
        num4 = ft_lstnew(&n4);
	a = NULL;
        a = num1;
        ft_lstadd_back(&a, num2);
        ft_lstadd_back(&a, num3);
        ft_lstadd_back(&a, num4);
        push_swap(&a);
        ft_lstclear(&a, free);
        return (0);
}

