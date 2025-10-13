/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:39:46 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/15 12:56:09 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_var(char *var, t_list **tmp_var) //cambiar por una funcion int? para poder registrar errores
{
    int         len;
    int         i;
    int         size;
    //char        *name;
    t_temp_lst  *var_line;

    len = (int) ft_strlen(var);
    size = ft_lstsize(*tmp_var);
    i = 0;
    while (i < size)
    {
        var_line = (t_temp_lst *) ((ft_lstpos(*tmp_var, i))->content);
        if (ft_strncmp(var, var_line->name, len + 1) == 0)
            return (ft_strdup(var_line->value));
        i++;
    }
    return (NULL);
}