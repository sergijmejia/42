/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:56:15 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/22 09:18:43 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	next_quote(char *str, int pos)
{
	char	c;

	c = str[pos];
	pos++;
	while (str[pos] && str[pos] != c)
		pos++;
	return (pos);
}

static char	*create_new(char **new, char *str, int start, int end)
{

}

static t_list	**double_list(t_list **token_list, int pos)
{
	t_list	*lst;
	char	str
	int		i;
	int		end;

	lst = ft_lstpos(*token_list, pos);
	if (lst == NULL)
		return (NULL);
	str = ((t_token *)(lst->content))->value;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			end = next_quote(str, i);
			str = create_new(&new_str, str, i, end);
			if (new_str == NULL)
				return (NULL);
			i = end;
		}
		i++;
	}
	free(str);
	((t_token *)(lst->content))->value = new_str;
	return (token_list);	
}*/

static int	count_new_len(char *str)
{
	int		inside;
	int		len;
	char	c;

	inside = 0;
	len = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (inside == 0)
			{
				c = *str;
				inside = 1;
			}
			else
			{
				if (*str == c)
					inside = 0;
				else
					len++;
			}
		}
		else
			len++;
		str++;
	}
	return (len);
}

static t_list	**quote_list(t_list **token_list, int pos)
{
	t_list	*lst;
	char	*str;
	char	*new_str;
	char	c;
	int		var[3];
	int		len;

	lst = ft_lstpos(*token_list, pos);
	if (lst == NULL)
		return (NULL);
	str = ((t_token *)(lst->content))->value;
	len = count_new_len(str);
	new_str = (char *) malloc (sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	new_str[len] = '\0';
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	c = '\0';
	while (str[var[0]])
	{
		if (str[var[0]] == '\'' || str[var[0]] == '\"')
		{
			if (var[2] == 0)
			{
				c = str[var[0]];
				var[2] = 1;
			}
			else
			{
				if (str[var[0]] == c)
					var[2] = 0;
				else
				{
					new_str[var[1]] = str[var[0]];
					var[1]++;
				}
			}
		}
		else
		{
			new_str[var[1]] = str[var[0]];
			var[1]++;
		}
		var[0]++;
	}
	free(str);
	((t_token *)(lst->content))->value = new_str;
	return (token_list);
}

t_list	**delete_quotes(t_list **token_list)
{
	int		i;
	int		len;
	t_list	*token_list_aux;
	t_token	*token;

	i = 0;
	len = ft_lstsize(*token_list);
	while (i < len)
	{
		token_list_aux = ft_lstpos(*token_list, i);
		token = (t_token *)(token_list_aux->content);
		if (!token_list_aux)
			return (error_list(token_list));
		if (token->type == 2 || token->type == 3 || token->type == 17)
		{
			if (quote_list(token_list, i) == NULL)
				return (error_list(token_list));
			token->finished = 1;
		}
		i++;
	}
	return (token_list);
}
