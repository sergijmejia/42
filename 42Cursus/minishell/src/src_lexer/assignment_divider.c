/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_divider.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:07:41 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/14 16:13:27 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que encuentra las proximas comillas*/
static int	next_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

/*Funcion que crea un nuevo nodo*/
static t_list	*create_node(char *str, int start, int end, int type)
{
	char	*str_token;
	t_token	*token;
	t_list	*new_node;

	str_token = (char *) malloc (sizeof(char) * (end - start + 2));
	if (!str_token)
		return (NULL);
	token = (t_token *) malloc (sizeof (t_token));
	if (!token)
	{
		free (str_token);
		return (NULL);
	}
	ft_strlcpy(str_token, &str[start], end - start + 2);
	token->value = str_token;
	if (type == 0)
		token->type = TOKEN_WORD;
	if (type == 9)
		token->type = TOKEN_ASSIGNMENT_CANDIDATE;
	token->finished = 0;
	new_node = ft_lstnew(token);
	if (!new_node)
		delete_token(token);
	return (new_node);
}

/*Funcion que verifica que el caracter c es correcto para el nombre*/
/*Si x = 0 estamos evaluando la primera letra. x = 1 cualquier otra letra*/
static int	correct_name_char(char c, int x)
{
	if (x == 0)
	{
		if (ft_isalpha(c) || c == '_')
			return (1);
		else
			return (0);
	}
	else
	{
		if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
			return (1);
		else
			return (0);
	}
}

/*Funcion que busca el inicio del assignment*/
static int	find_start_assignment(char *str, int pos)
{
	int		i;
	char	space[4];

	space[0] = 9;
	space[1] = 10;
	space[2] = 32;
	space[3] = 0;
	i = pos - 1;
	if (i == -1)
		return (-1);
	while (i >= 0 && correct_name_char(str[i], 1))
		i--;
	if (i == -1)
	{
		if (correct_name_char(str[0], 0))
			return (0);
		return (-1);
	}
	if (ft_strcontains(&space[0], str[i]) && correct_name_char(str[i + 1], 0))
		return (i + 1);
	else
		return (-1);
}

/*Funcion que busca el final del asssignment*/
static int	find_end_assignment(char *str, int pos)
{
	char	spacing_char[4];

	spacing_char[0] = 9;
	spacing_char[1] = 10;
	spacing_char[2] = 32;
	spacing_char[3] = 0;
	while (str[pos])
	{
		if (ft_strcontains(&spacing_char[0], str[pos]))
			return (pos);
		if (str[pos] == '\'' || str[pos] == '\"')
			pos = pos + 1 + next_quote(&str[pos + 1], str[pos]);
		pos++;
	}
	return (pos);
}

/*Funcion que genera el puntero doble para n *t_list*/
static t_list	**define_list_nulls(int n)
{
	t_list	**new_nodes;
	int		i;

	new_nodes = (t_list **) malloc (n * sizeof(t_list *));
	if (new_nodes == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_nodes[i] = NULL;
		i++;
	}
	return (new_nodes);
}

/*Funcion que gestiona la definicion del nodo inicial si start > 0*/
static t_list	**start_node(t_list **new_nodes, char *str, int start)
{
	new_nodes[0] = create_node(str, 0, start - 1, 0);
	if (new_nodes[0] == NULL)
	{
		free(new_nodes[1]);
		free(new_nodes[2]);
		free(new_nodes);
		return (NULL);
	}
	return (new_nodes);
}

/*Funcion que gestiona la definicion de nodo assignment*/
static t_list	**assignment_node(t_list **new, char *str, int start, int end)
{
	new[1] = create_node(str, start, end, 9);
	if (new[1] == NULL)
	{
		free(new[0]);
		free(new[2]);
		free(new);
		return (NULL);
	}
	return (new);
}

/*Funcion que gestiona la definicion del nodo final si len -1 >= end + 1*/
static t_list	**final_node(t_list **new_nodes, char *str, int end, int len)
{
	new_nodes[2] = create_node(str, end + 1, len - 1, 0);
	if (new_nodes[2] == NULL)
	{
		free(new_nodes[0]);
		free(new_nodes[1]);
		free(new_nodes);
		return (NULL);
	}
	return (new_nodes);
}

/*Funcion que genera los nuevos nodos*/
static t_list	**generate_nodes(t_list **lst, int i, int start, int end)
{
	int		len;
	char	*str;
	t_list	**new_nodes;

	str = ((t_token *)(ft_lstpos(*lst, i)->content))->value;
	new_nodes = define_list_nulls(3);
	if (new_nodes == NULL)
		return (NULL);
	if (start > 0)
	{
		if (start_node(new_nodes, str, start) == NULL)
			return (NULL);
	}
	if (assignment_node(new_nodes, str, start, end) == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (len -1 >= end + 1)
	{
		if (final_node(new_nodes, str, end, len) == NULL)
			return (NULL);
	}
	return (new_nodes);
}

/*Funcion que agrega los nuevos nodos*/
static t_list	**add_nodes(t_list **lst, t_list **new, int *i, int pos[2])
{
	int		len;
	char	*str;

	str = ((t_token *)(ft_lstpos(*lst, *i)->content))->value;
	len = ft_strlen(str);
	ft_lstdel_pos(lst, delete_token, *i);
	if (pos[0] > 0)
	{
		ft_lstadd_pos(lst, new[0], *i);
		(*i)++;
	}
	ft_lstadd_pos(lst, new[1], *i);
	if (len - 1 >= pos[1] + 1)
	{
		(*i)++;
		ft_lstadd_pos(lst, new[2], *i);
	}
	free(new);
	return (lst);
}

/*Funcionn que crea un TOKEN_ASSIGNMENT_CANDIDATE*/
static int	assignment_candidate(t_list **lst, int *i, int pos)
{
	int		start_end[2];
	char	*str_token;
	t_token	*token;
	t_list	**new_nodes;

	token = (t_token *)(ft_lstpos(*lst, *i)->content);
	str_token = token->value;
	start_end[0] = find_start_assignment(str_token, pos);
	if (start_end[0] != -1)
	{
		start_end[1] = find_end_assignment(str_token, pos + 1) - 1;
		if (start_end[1] != -1)
		{
			new_nodes = generate_nodes(lst, *i, start_end[0], start_end[1]);
			if (new_nodes == NULL)
				return (-1);
			if (add_nodes(lst, new_nodes, i, start_end) == NULL)
				return (-1);
			else
				return (1);
		}
	}
	return (0);
}

/*Funcion que encuentra el siguiente '='*/
static int	find_next_equal(char *str, int pos)
{
	while (str[pos])
	{
		if (str[pos] == '=')
			return (pos);
		if (str[pos] == '\'' || str[pos] == '\"')
			pos = pos + 1 + next_quote(&str[pos + 1], str[pos]);
		pos++;
	}
	return (-1);
}

/*Funcio que encuentra todos los TOKEN_ASSIGNMENT_CANDIDATE*/
static t_list	**divide_assignment(t_list **token_list, int *i)
{
	int		pos;
	int		assignment;
	char	*str;
	t_list	*lst;

	lst = ft_lstpos(*token_list, *i);
	if (!lst)
		return (NULL);
	str = ((t_token *)(lst->content))->value;
	pos = find_next_equal(str, 0);
	while (pos > 0)
	{
		assignment = assignment_candidate(token_list, i, pos);
		if (assignment == -1)
			return (error_list(token_list));
		else if (assignment == 0)
			pos = find_next_equal(str, pos + 1);
		else
			break ;
	}
	return (token_list);
}

/*Funcion que divide cada uno de los TOKEN_WORD por espacios*/
t_list	**assignment_divider(t_list **token_list)
{
	int		len;
	int		i;
	t_list	*token_list_aux;

	len = ft_lstsize(*token_list);
	i = 0;
	while (i < len)
	{
		token_list_aux = ft_lstpos(*token_list, i);
		if (!token_list_aux)
			return (error_list(token_list));
		if (((t_token *)(token_list_aux->content))->type == TOKEN_WORD)
		{
			if (divide_assignment(token_list, &i) == NULL)
				return (error_list(token_list));
		}
		i++;
		len = ft_lstsize(*token_list);
	}
	return (token_list);
}
