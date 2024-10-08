/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:00:14 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/08 15:34:31 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**pnt;
	t_list	*f_list;

	if ((lst == NULL) || (f == NULL) || (del == NULL))
		return (NULL);

	f_list = NULL;
	pnt = &f_list;
	while (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (aux == NULL)
		{
			ft_lstclear
		}
		ft_lstadd_back(pnt, aux);
	}
}
