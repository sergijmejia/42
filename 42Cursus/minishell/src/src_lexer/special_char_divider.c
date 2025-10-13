/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_divider.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:27:55 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/13 13:06:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*Funcion que crear un nuevo token para agregarla a lst original*/
static t_list	*create_new_lst_token(t_list *lst, int pos)
{
	int		len_str;
	char	*str;
	t_token	*token;
	t_token	*new_token;
	t_list	*new_list_token;

	token = (t_token *)(lst->content);
	len_str = (int) ft_strlen(token->value);
	str = ft_substr(token->value, pos, len_str);
	if (!str)
		return (NULL);
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free(str);
		return (NULL);
	}
	new_token->value = str;
	new_token->finished = 0;
	new_list_token = ft_lstnew(new_token);
	if (!new_list_token)
		delete_token(new_token);
	new_token->type = check_type(new_list_token);
	return (new_list_token);
}

/*Funcion que localiza la posicion de espacio, tabulacion o fin linea*/
static int	ft_pos_special(char *str, const char *special_char)
{
	int	pos;
	int	len;

	pos = 0;
	len = (int) ft_strlen(str);
	while (str[pos])
	{
		if (str[pos] == '\'' || str[pos] == '\"')
			pos = next_quote(str, pos);
		if (ft_strcontains(special_char, str[pos]))
		{
			if (str[pos] != '&')
				break ;
			else
			{
				if (str[pos + 1] == '&')
					break ;
			}
		}
		pos++;
	}
	if (pos == len)
		pos = -1;
	return (pos);
}

/*Funcion que agrega un nodo de caracter especial al la lista*/
static t_list	**create_special(t_list **token_list, int i)
{
	char	*str;
	t_list	*token;

	token = ft_lstpos(*token_list, i);
	str = ((t_token *)(token->content))->value;
	if ((str[0] == '$') && (str[1] == '?'))
	{
		if (special_char(token_list, i, 2) == NULL)
			return (NULL);
	}
	else if ((str[0] == str[1]) && (str[0] != ')') && (str[0] != '('))
	{
		if (special_char(token_list, i, 2) == NULL)
			return (NULL);
	}
	else
	{
		if (special_char(token_list, i, 1) == NULL)
			return (NULL);
	}
	return (token_list);
}

/*Funcion que agrega un nodo que contiene str previo al caracter especial*/
static t_list	**create_not_special(t_list **token_list, int pos, int i)
{
	char	*str;
	t_list	*lst;
	t_token	*token;
	t_list	*new_list_token;

	lst = ft_lstpos(*token_list, i);
	token = (t_token *)(lst->content);
	str = ft_substr(token->value, 0, pos);
	if (!str)
		return (NULL);
	new_list_token = create_new_lst_token(lst, pos);
	free(((t_token *)(lst->content))->value);
	((t_token *)(lst->content))->value = str;
	((t_token *)(lst->content))->type = check_type(lst);
	if (!new_list_token)
		return (NULL);
	ft_lstadd_pos(token_list, new_list_token, i + 1);
	return (token_list);
}

/*Funcion que divide los TOKEN_WORD de los caracteres especiales*/
static t_list	**divide_special(t_list **token_list, int *i, char *sp_char)
{
	t_list	*lst;
	t_token	*token;
	int		pos;

	lst = ft_lstpos(*token_list, *i);
	if (lst == NULL)
		return (token_list);
	token = (t_token *)(lst->content);
	pos = ft_pos_special(token->value, sp_char);
	if (pos == -1)
		return (token_list);
	else if (pos == 0)
	{
		if (create_special(token_list, *i) == NULL)
			return (NULL);
	}
	else
	{
		if (create_not_special(token_list, pos, *i) == NULL)
			return (NULL);
	}
	(*i)++;
	return (divide_special(token_list, i, sp_char));
}

/*Funcion que define los special char*/
static void	define_special(char *special_char)
{
	special_char[0] = '<';
	special_char[1] = '>';
	special_char[2] = '|';
	special_char[3] = '&';
	special_char[4] = ')';
	special_char[5] = '(';
	special_char[6] = 0;
	return ;
}

/*Funcion para buscar los caracteres especiales en todos los TOKEN_WORD*/
t_list	**special_char_divider(t_list **token_list)
{
	int		len;
	int		i;
	t_list	*token_list_aux;
	t_token	*token;
	char	special_char[7];

	len = ft_lstsize(*token_list);
	define_special(&special_char[0]);
	i = 0;
	while (i < len)
	{
		token_list_aux = ft_lstpos(*token_list, i);
		token = (t_token *)(token_list_aux->content);
		if (!token_list_aux)
			return (error_list(token_list));
		if (token->finished == 0)
		{
			if (token->type == 0 || token->type == 2 || token->type == 3)
				if (divide_special(token_list, &i, &special_char[0]) == NULL)
					return (error_list(token_list));
		}
		i++;
		len = ft_lstsize(*token_list);
	}
	return (token_list);
}
