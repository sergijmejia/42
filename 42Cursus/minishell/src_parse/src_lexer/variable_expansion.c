/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:36:48 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 10:36:39 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona el loop de variable_expansion*/
t_list	**var_expansion_loop(t_list **lst, char **env, int i, t_list **tmp_var)
{
	t_token	*token;

	token = (t_token *)((ft_lstpos(*lst, i))->content);
	if (token->type == TOKEN_WORD && token->finished == 0)
	{
		if (exp_string(lst, env, i, tmp_var) == NULL)
			return (NULL);
	}
	else if (token->type == TOKEN_EXPANDIBLE_STRINGS && token->finished == 0)
	{
		if (exp_string(lst, env, i, tmp_var) == NULL)
			return (NULL);
	}
	else if (token->type == TOKEN_ASSIGNMENT_CANDIDATE && token->finished == 0)
	{
		if (exp_string(lst, env, i, tmp_var) == NULL)
			return (NULL);
	}
	else if (token->type == TOKEN_REDIRECTION_WORD)
	{
		if (exp_string(lst, env, i, tmp_var) == NULL)
			return (NULL);
	}
	return (lst);
}

/*Funcion que gestiona la exansion de variables*/
t_list	**var_expansion(t_list **token_list, char **env, t_list **tmp_var)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = ft_lstpos(*token_list, i);
	while (lst != NULL)
	{
		if (var_expansion_loop(token_list, env, i, tmp_var) == NULL)
			return (error_list(token_list));
		i++;
		lst = ft_lstpos(*token_list, i);
	}
	return (token_list);
}
