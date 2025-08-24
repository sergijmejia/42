/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_divider.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:27:55 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/22 20:07:04 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crear una lueva lista para agregarla a lst original*/
static t_list	*create_new_lst_token(t_list *token, int pos)
{
	int		len_str;
	char	*str;
	t_token	*new_token;
	t_list	*new_list_token;

	len_str = (int) ft_strlen(((t_token *)(token->content))->value); 
	str = ft_substr(((t_token *)(token->content))->value, pos, len_str);
	if (!str)
		return NULL;
	new_token = (t_token *) malloc (sizeof (t_token));
	if (!new_token)
	{
		free(str);
		retur (NULL);
	}
	new_token->value = str;
	new_token->type = TOKEN_WORD;
	new_list_token = ft_lstnew(new_token);
	if (new_list_token)
		delete_token(new_token);
	return (new_list_token);
}

/*Funcion que localiza la posicion de espacio, tabulacion o fin linea*/
static int	ft_pos_special(char *str, char *special_char)
{
	int	pos;
	int	len;

	pos = 0;
	len = (int) ft_strlen(str);
	while (str[pos])
	{
		if (ft_strcontains(special_char, str[pos]))
			break ;
		pos++;
	}
	if (pos == len)
		pos = -1;
	return (pos);
}

/*Funcion que agrega un nodo de caracter especial al la lista*/
static void	create_special(t_list **token_list, int i)
{
	char	*str;
	t_list	*token;

	token = ft_lstpos(*token_list, i);
	str = ((t_token *)(token->content))->value;
	if ((str[0] == str[1]) && (str[0] != ')') && (str[0] != '('))
		double_special_char(token_list, i);
	else
		simple_special_char(token_list, i);
	return ;
}

/*Funcion que divide los TOKEN_WORD de los caracteres especiales*/
static int	divide_special(t_list **token_list, int i, char *special_char)
{
	t_list	*token;
	t_list	*new_list_token;
	char	*str;
	int		pos;

	token = ft_lstpos(*token_list, i);
	if ((token == NULL) || (((t_token *)(token->content))->type != TOKEN_WORD))
		return (i);
	pos = ft_pos_special(((t_token *)(token->content))->value, special_char);
	if (pos == -1)
		return (i);
	else if (pos == 0)
		create_special(token_list, i);
	else
	{
		str = ft_substr(((t_token *)(token->content))->value, 0, pos);
		if (!str)
			error_list(token_list);
		new_list_token = create_new_lst_token(token, pos);
		if (!new_list_token)
			error_token(token_list, str);
		free(((t_token *)(token->content))->value);
		((t_token *)(token->content))->value = str;
		ft_lstadd_pos(token_list, new_list_token, i);
	}
	i++;
	return (divide_special(token_list, i, special_char));
}

/*Funcion para buscar los caracteres especiales en todos los TOKEN_WORD*/
void    special_char_divider(t_list **token_list)
{
	int		len;
	int		i;
	t_list	*token_list_aux;
	char	special_char[7];

	len = ft_lstsize(*token_list);
	special_char[0] = '<';
	special_char[1] = '>';
	special_char[2] = '|';
	special_char[3] = '&';
	special_char[4] = ')';
	special_char[5] = '(';
	special_char[6] = 0;
	i = 0;
	while (i < len)
	{
		token_list_aux = ft_lstpos(*token_list, i);
		if (!token_list_aux)
			error_list(token_list);
		if (((t_token *)(token_list_aux->content))->type == TOKEN_WORD) 
			i = divide_special(token_list, i, &special_char[0]);
		if (i == -1)
			error_list(token_list);
		i++;
		len = ft_lstsize(*token_list);
	}
}
