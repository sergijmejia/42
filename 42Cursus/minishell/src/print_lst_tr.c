/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst_tr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:48:18 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/17 17:15:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Imprime por pantalla la lista lst*/
void	print_lst_tr(t_list *lst)
{
	t_token_ast	*token;
	char		**str;
	int			len;
	int			i;

	if (lst == NULL)
		return ;
	token = (t_token_ast *) (lst->content);
	str = (char **)(token->value);
	len = 0;
	while (str[len])
		len++;
	i = 0;
	while (i < len)
	{
		ft_printf("%s", str[i]);
		i++;
		if (i != len)
			ft_printf(", ");
	}
	ft_printf("    (%d)\n", token->type);
	if (lst->next != NULL)
	{
		print_lst_tr(lst->next);
		return ;
	}
}
