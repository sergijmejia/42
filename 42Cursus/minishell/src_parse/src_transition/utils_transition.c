/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_transition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:49:55 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 13:24:19 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica si hay wildcard en el comando*/
static int	check_wildcard(t_list **lst, int pos)
{
	int		wildcard;
	int		type;
	int		len;

	wildcard = 0;
	len = ft_lstsize(*lst);
	while (pos < len)
	{
		type = ((t_token *)((ft_lstpos(*lst, pos))->content))->type;
		if (!((type >= 0 && type <= 3) || type == 16))
			break ;
		if (type == 16)
		{
			wildcard = 1;
			break ;
		}
		pos++;
	}
	return (wildcard);
}

/*Funcion que crea el string doble para el comando*/
static char	**create_str_command(t_list **lst, int start, int end)
{
	char	**str;
	char	*str_lst;
	int		i;

	str = ft_calloc (end - start + 1, sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str_lst = ((t_token *)((ft_lstpos(*lst, start))->content))->value;
		if (!(ft_strlen(str_lst) == 0))
		{
			str[i] = ft_strdup(str_lst);
			if (!str[i])
				return (free_str(str));
			i++;
		}
		start++;
	}
	str[i] = NULL;
	return (str);
}

/*Funcion que calcula el la longitud del string doble para el comando*/
static char	**str_command(t_list **lst, int *pos)
{
	char	**str;
	int		type;
	int		start;
	int		len;

	start = *pos;
	len = ft_lstsize(*lst);
	while (*pos < len)
	{
		type = ((t_token *)((ft_lstpos(*lst, *pos))->content))->type;
		if (!((type >= 0 && type <= 3) || type == 16))
			break ;
		(*pos)++;
	}
	str = create_str_command(lst, start, *pos);
	if (!str)
		return (NULL);
	return (str);
}

/*Funcion que crea un nuevo token de transicion*/
t_token_ast	*create_new_tr_token(char **str, t_type_lexer type, int w, int qte)
{
	t_token_ast	*new_token;
	t_type_tr	tr_type;

	new_token = (t_token_ast *) malloc (sizeof(t_token_ast));
	if (!new_token)
		return (NULL);
	new_token->value = str;
	if (type == 0)
		tr_type = 0;
	else if (type == 17 || type == 18)
	{
		tr_type = 11;
		if (type == 18)
			new_token->quote = qte;
	}
	else
	{
		if (type >= 4 && type <= 8)
			tr_type = type - 3;
		else
			tr_type = type - 4;
	}
	new_token->type = tr_type;
	new_token->wildcard = w;
	return (new_token);
}

/*Funcion que crea el nodo de transicion para los comandos*/
t_list	*command_node(t_list **token_list, int *pos, int quote)
{
	char		**str;
	int			wildcard;
	t_token_ast	*new_token;
	t_list		*new_node;

	wildcard = check_wildcard(token_list, *pos);
	str = str_command(token_list, pos);
	new_token = create_new_tr_token(str, 0, wildcard, quote);
	if (!new_token)
	{
		free_str(str);
		return (NULL);
	}
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		free_str(str);
		delete_token_ast(new_token);
		return (NULL);
	}
	return (new_node);
}
