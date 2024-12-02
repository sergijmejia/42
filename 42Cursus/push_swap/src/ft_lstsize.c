/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:18:10 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/06 03:44:36 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	if (lst == NULL)
		return (len);
	len = 1 + ft_lstsize(lst->next);
	return (len);
}
/*
int	main(void)
{
	t_list	*multi_node_list;
	int	*num;
	int	n[3];

	n[0] = 1;
	n[1] = 2;
	n[2] = 3;
	num = &n[0];
	multi_node_list = ft_lstnew(num);
	num++;
	multi_node_list->next = ft_lstnew(num);
	num++;
	multi_node_list->next->next = ft_lstnew(num);
	printf("Tamano de la lista multi-node: %d\n", ft_lstsize(multi_node_list));
	return (0);
}
*/
