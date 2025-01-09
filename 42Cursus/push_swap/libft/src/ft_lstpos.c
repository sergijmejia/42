/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:47:10 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/09 13:50:37 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Devuelve un puntero a la posicion x de la lista lst*/
t_list	*ft_lstpos(t_list *lst, int x)
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
