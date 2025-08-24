/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_divider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:55:03 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/19 20:08:25 by smejia-a         ###   ########.fr       */
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
	new_list_token = ft_lstnew(new_token);
	if (!new_list_token)
		delete_token(new_token);
	return (new_list_token);
}

/*Funcion que localiza la posicion de espacio, tabulacion o fin linea*/
static int	ft_pos_char(char *str)
{
	int	pos;
	int	len;

	pos = 0;
	len = (int) ft_strlen(str);
	while (str[pos] && str[pos] != 32 && str[pos] != 9 && str[pos] != 10)
		pos++;
	if (pos == len)
		pos = -1;
	return (pos);
}

/*Funcion que divide un TOKEN_WORD por espacios*/
static int	divide_space(t_list **token_list, int i, char *trim_char)
{
	t_list	*first_token;
	t_list	*new_list_token;
	char	*str;
	int		pos;

	first_token = ft_lstpos(*token_list, i);
	if (!first_token)
		error_list(token_list);
	str = ft_strtrim((((t_token *)(first_token->content))->value), trim_char);
	if (!str)
		error_list(token_list);
	free(((t_token *)(first_token->content))->value);
	((t_token *)(first_token->content))->value = str;
	pos = ft_pos_char(((t_token *)(first_token->content))->value);
	if (pos == -1)
		return (i);
	else
	{
		new_list_token = create_new_lst_token(first_token, pos);
		if (!new_list_token)
			error_list(token_list);
		str = ft_substr(((t_token *)(first_token->content))->value, 0, pos);
		if (!str)
		{
			ft_lstclean(&new_list_token, delete_token);
			error_list(token_list);
		}
		free(((t_token *)(first_token->content))->value);
		((t_token *)(first_token->content))->value = str;
		ft_lstadd_pos(token_list, new_list_token, i);
	}
	i++;
	return (divide_space(token_list, i, trim_char));
}

/*Funcion que divide cada uno de los TOKEN_WORD por espacios*/
void	space_divider(t_list **token_list)
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
			error_list(token_list);
		if (((t_token *)(token_list_aux->content))->type == TOKEN_WORD)
			i = divide_space(token_list, i, &trimming_char[0]);
		i++;
		len = ft_lstsize(*token_list);
	}
}
