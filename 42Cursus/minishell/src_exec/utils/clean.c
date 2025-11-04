/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:21:59 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:22:06 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

/* Frees executor dynamic list */
void	free_tmp_var_exec(t_temp_lst_exec *lst)
{
	t_temp_lst_exec	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->name);
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}
