/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:14:32 by smejia-a          #+#    #+#             */
/*   Updated: 2025/05/24 12:15:40 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Imprime por pantalla la lista lst*/
void	print_lst(t_list *lst)
{
	if (lst == NULL)
		return ;
	ft_printf("%d ", *(char *)(lst->content));
	if (lst->next != NULL)
	{
		print_lst(lst->next);
		return ;
	}
}
