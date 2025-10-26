/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:46:48 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 15:05:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**create_var_table(void)
{
	t_list		**var_lst;

	var_lst = (t_list **) malloc (sizeof(t_list *));
	if (!var_lst)
		return (NULL);
	*var_lst = NULL;
	return (var_lst);
}
