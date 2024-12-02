
static t_list	ft_lstdup(t_list *lst)
{
	t_list	*new_lst;
	int	len;

	if(lst == NULL)
		return (NULL);
	new_lst = malloc (sizeof(t_list));
	if(new_lst == NULL)
	{
		return (NULL);
	}
	new_lst->content = lst->content;
	new_lst->next = ft_lstdup(lst->next);
	return (new_lst);
}	


int	push_swap(t_list *a)
{
	//*lst->content es el numero en la posicion 1
	//*lst->next apunta al siguiente elemento
	
	int		len;
	int		result;
	t_list	*b;
	t_list	*lst;

	result = 0;
	len = ft_lstsize(a);
	lst = ft_lstdup(a);
	if(ft_lstsize(lst) != len)
	{
		ft_lstclear(lst, free);
		return (result);
	}
	bubble_sort(&lst, len);

}
