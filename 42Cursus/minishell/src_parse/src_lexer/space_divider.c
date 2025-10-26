/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_divider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:55:03 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 13:52:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que localiza la posicion de espacio, tabulacion o fin de linea*/
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
		if (node_before_div(token_list, *i, pos) == NULL)
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
