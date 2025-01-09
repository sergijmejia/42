/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsecondlast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:49:03 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/09 13:50:12 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Devuelve un puntero al penultimo elemmento de la lista lst*/
t_list	*ft_lstsecondlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (NULL);
	if ((lst->next)->next == NULL)
		return (lst);
	return (ft_lstsecondlast(lst->next));
}
