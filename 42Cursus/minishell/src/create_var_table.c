/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:46:48 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/12 14:46:48 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list  **create_var_table(void)
{
    t_list  **var_lst;
    t_list  *test_node;
    t_temp_lst  *test_tmp;

    var_lst = (t_list **) malloc (sizeof(t_list *));
	if (!var_lst)
		return (NULL);
    *var_lst = NULL;
   
//--------------Esta parte es para testear
    test_node = (t_list *) malloc (sizeof(t_list));
    test_node->next=NULL;
    test_tmp = (t_temp_lst *) malloc (sizeof(t_temp_lst));
    test_tmp->name = ft_strdup("VAR");
    test_tmp->value = ft_strdup("adios mundo");


    test_node->content = test_tmp;
    *var_lst = test_node;
    return (var_lst);
}
