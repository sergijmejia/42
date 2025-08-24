/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:36:48 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/22 21:16:56 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_lstpos(t_list **token_list, t_list **new_list, int x)
{
	ft_lstlast(*new_list)->ft_lstpos(*token_list, x)->next;
	ft_lstdel_pos(token_list, delete_token, x);
	if (x == 0)
		token_list = new_list;
	else
		ft_lstpos(*token_list, x - 1)->next = new_list;
}

static void	word(t_list **token_list, int x)
{
	int		len;
	char	*str;
	t_list	**new_lst;

	str = token_list[x]->content->value;
	len = (int) ft_strlen(str);
	if (str[0] == '$' && len > 1)
	{
		new_lst = lexer(getenv(&str[1]));
		replace_lstpos(token_list, new_lst, x);
	}
	
}

static int	include_string(char **str, int pos)
{
	int		j;
	int		new_len;
	char	*command;
	char	*expanded_str;
	char	*new_str;

	j = pos + 1;
	len = 0;
	while (ft_isalpha((*str)[j]) || ft_isdigit((*str)[j]) || (*str)[j] == '_')
		len++;
	command = malloc (len + 2);
	ft_strlcpy(&command[0], &(*str)[pos], len + 2);
	expanded_str = getenv(command);
	free(command);
	new_len = (int) (ft_strlen(expanded_str) + ft_strlen(*str) - len);
	new_str = malloc(new_len + 1);
	if (!new_str)
		error_list(token_list);
	new_str[len + 2] = '\0';
	ft_strlcpy(&new_str[0], *str, pos);
	ft_strlcpy(&new_str[pos + 1], expanded_str, len);
	ft_strlcpy(&new_str[i + len + 1], &(*str)[pos + len + 1], len);
	free(*str);
	*str = new_str;
	return (pos + ft_srlen(expanded_str));
}

static void	expandible_string(t_list **token_list, int x)
{
	int		i;

	i = 0;
	str = token_list[x]->content->value;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			if (str[i + 1] == '?')
			{
				/*Tenemos que almacenar el valor del ultimo (exit status)*/
				return ;
			}
			else
				i = include_string(&str, i);
		}
		else
			i++;
	}
}

void	variable_expansion(t_list **token_list)
{
	int		i;

	if (token_list == NULL)
		return ;
	i = 0;
	while (token_list[i])
	{
		if (token_list[i]->content->type == TOKEN_WORD)
			word(token_list, i)
		else if (token_list[i]->content->type == TOKEN_EXPANDIBLE_STRING)
			expandible_string(token_list, i);
		i++;
	}
}
