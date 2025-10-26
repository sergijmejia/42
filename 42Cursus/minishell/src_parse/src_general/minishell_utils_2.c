/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:58:28 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 16:59:07 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que duplica un token*/
t_token	*duplicate_token(t_token *token)
{
	t_token	*new_token;
	char	*str;

	new_token = (t_token *) malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	str = ft_strdup(token->value);
	if (!str)
	{
		free(new_token);
		return (NULL);
	}
	new_token->value = str;
	new_token->type = token->type;
	new_token->finished = token->finished;
	new_token->quote = token->quote;
	return (new_token);
}

/*Funcion que encuentra la siguiente comilla*/
int	next_quote(char *str, int pos)
{
	char	c;

	c = str[pos];
	pos++;
	while (str[pos] && str[pos] != c)
		pos++;
	return (pos);
}

/*Verifica el type*/
t_type_lexer	check_type(t_list *lst)
{
	char	*str;
	int		literal;
	int		i;

	literal = 0;
	i = 0;
	str = ((t_token *)(lst->content))->value;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i = next_quote(str, i);
			literal = 1;
		}
		if (str[i] == '\"')
			return (TOKEN_EXPANDIBLE_STRINGS);
		i++;
	}
	if (literal == 1)
		return (TOKEN_STRING_LITERAL);
	else
		return (TOKEN_WORD);
}

/*Funcion que duplica el value del token_ast*/
static char	**duplicate_token_tr_str(t_token_ast *token)
{
	char	**str;
	char	**new_str;
	int		i;
	int		len;

	len = calculate_strlen(token);
	if (len == -1)
		return (NULL);
	str = token->value;
	new_str = (char **) malloc ((len + 1) * sizeof(char *));
	if (new_str == NULL)
		return (NULL);
	new_str[len] = NULL;
	i = 0;
	while (i < len)
	{
		new_str[i] = strdup(str[i]);
		if (new_str[i] == NULL)
		{
			free_str(new_str);
			return (NULL);
		}
		i++;
	}
	return (new_str);
}

/*Funcion que duplica un token_ast*/
t_token_ast	*duplicate_token_tr(t_token_ast *token)
{
	t_token_ast	*new_token;
	char		**new_str;

	new_str = duplicate_token_tr_str(token);
	if (new_str == NULL)
		return (NULL);
	new_token = (t_token_ast *) malloc (sizeof(t_token_ast));
	if (!new_token)
	{
		free_str(new_str);
		return (NULL);
	}
	new_token->value = new_str;
	new_token->type = token->type;
	new_token->wildcard = token->wildcard;
	return (new_token);
}
