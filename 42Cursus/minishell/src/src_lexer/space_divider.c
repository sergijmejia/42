/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_divider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:55:03 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/13 14:24:58 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crear una lueva lista para agregarla a lst original*/
static t_list	*create_new_lst_token(t_list *token, int pos_space)
{
	int		len_str;
	char	*str;
	t_token	*new_token;
	t_list	*new_list_token;

	len_str = (int) ft_strlen(((t_token *)(token->content))->value);
	str = ft_substr(((t_token *)(token->content))->value, pos_space, len_str);
	if (!str)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free (str);
		return (NULL);
	}
	new_token->value = str;
	new_token->type = TOKEN_WORD;
	new_token->finished = 0;
	new_list_token = ft_lstnew(new_token);
	if (!new_list_token)
		delete_token(new_token);
	return (new_list_token);
}

/*Funcion que encuentra la siguiente comilla*/
static int	next_quote(char *str, int pos)
{
	char	c;

	c = str[pos];
	pos++;
	while (str[pos] && str[pos] != c)
		pos++;
	return (pos);
}

/*Funcion que localiza la posicion de espacio, tabulacion o fin linea*/
static int	ft_pos_char(char *str)
{
	int	pos;
	int	len;

	pos = 0;
	len = (int) ft_strlen(str);
	while (str[pos] && str[pos] != 32 && str[pos] != 9 && str[pos] != 10)
	{
		if (str[pos] == '\'' || str[pos] == '\"')
			pos = next_quote(str, pos);
		pos++;
	}
	if (pos == len)
		pos = -1;
	return (pos);
}

/*Verifica el type*/
static t_type_lexer	check_type(t_list *lst)
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

/*Funcion que crea el nodo que contiene el string previo al divisor*/
static t_list	**create_before_space(t_list **token_list, int i, int pos)
{
	t_list	*first_token;
	t_list	*new_list_token;
	char	*str;

	first_token = ft_lstpos(*token_list, i);
	if (!first_token)
		return (NULL);
	new_list_token = create_new_lst_token(first_token, pos);
	if (!new_list_token)
		return (NULL);
	str = ft_substr(((t_token *)(first_token->content))->value, 0, pos);
	if (!str)
	{
		ft_lstclear(&new_list_token, delete_token);
		return (NULL);
	}
	free(((t_token *)(first_token->content))->value);
	((t_token *)(first_token->content))->value = str;
	((t_token *)(first_token->content))->type = check_type(first_token);
	ft_lstadd_pos(token_list, new_list_token, i + 1);
	return (token_list);
}

/*Funcion que maneja el caso de un string vacio*/
static t_list	**empty_str(t_list **token_list, int *i, char *str)
{
	ft_lstdel_pos(token_list, delete_token, *i);
	(*i)--;
	free(str);
	return (token_list);
}

/*Funcion que divide un TOKEN_WORD por espacios*/
static t_list	**divide_space(t_list **token_list, int *i, char *trim_char)
{
	t_list	*first_token;
	char	*str;
	int		pos;

	first_token = ft_lstpos(*token_list, *i);
	str = ft_strtrim((((t_token *)(first_token->content))->value), trim_char);
	if (!str)
		return (NULL);
	if (*str == '\0')
		return (empty_str(token_list, i, str));
	free(((t_token *)(first_token->content))->value);
	((t_token *)(first_token->content))->value = str;
	pos = ft_pos_char(str);
	if (pos == -1)
	{
		((t_token *)(first_token->content))->type = check_type(first_token);
		return (token_list);
	}
	else
	{
		if (create_before_space(token_list, *i, pos) == NULL)
			return (NULL);
	}
	(*i)++;
	return (divide_space(token_list, i, trim_char));
}

/*Funcion que divide cada uno de los TOKEN_WORD por espacios*/
t_list	**space_divider(t_list **token_list)
{
	int		len;
	int		i;
	t_list	*token_list_aux;
	char	trimming_char[4];

	len = ft_lstsize(*token_list);
	trimming_char[0] = 9;
	trimming_char[1] = 10;
	trimming_char[2] = 32;
	trimming_char[3] = 0;
	i = 0;
	while (i < len)
	{
		token_list_aux = ft_lstpos(*token_list, i);
		if (!token_list_aux)
			return (error_list(token_list));
		if (((t_token *)(token_list_aux->content))->type == TOKEN_WORD)
		{
			if (divide_space(token_list, &i, &trimming_char[0]) == NULL)
				return (error_list(token_list));
		}
		i++;
		len = ft_lstsize(*token_list);
	}
	return (token_list);
}
