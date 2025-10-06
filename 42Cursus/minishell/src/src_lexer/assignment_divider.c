/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_divider.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:07:41 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/18 16:42:17 by smejia-a         ###   ########.fr       */
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

/*static t_list *ft_malloc(int x)
{
    if (x == 0)
        return (NULL);
    return (NULL);
}*/

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
static int	correct_name_char(char	c, int x)
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

/*Funcion que agrega los nuevos nodos*/
static t_list	**add_nodes(t_list **token_list, int *i, int start, int end)
{
	int		len;
	char	*str;
	t_list	*lst_token_word_start;
	t_list	*lst_token_word_end;
	t_list	*lst_token_assignment;

	str = ((t_token *)(ft_lstpos(*token_list, *i)->content))->value;
	if (start > 0)
	{
		lst_token_word_start = create_node(str, 0, start - 1, 0);
		if (lst_token_word_start == NULL)
			return (NULL);
	}
	lst_token_assignment = create_node(str, start, end, 9);
	if (lst_token_assignment == NULL)
	{
		ft_lstdelone(lst_token_word_start, delete_token);
		return (NULL);
	}
	len = ft_strlen(str);
	if (len -1 >= end + 1)
	{
		lst_token_word_end = create_node(str, end + 1, len - 1, 0);
		if (lst_token_word_end == NULL)
		{
			ft_lstdelone(lst_token_word_start, delete_token);
			ft_lstdelone(lst_token_assignment, delete_token);
			return (NULL);
		}
	}
	ft_lstdel_pos(token_list, delete_token, *i);
	if (start > 0)
	{
		ft_lstadd_pos(token_list, lst_token_word_start, *i);
		(*i)++;
	}
	ft_lstadd_pos(token_list, lst_token_assignment, *i);
	if (len -1 >= end + 1)
	{
		(*i)++;
		ft_lstadd_pos(token_list, lst_token_word_end, *i);
	}
	return (token_list);
}

/*Funcionn que crea un TOKEN_ASSIGNMENT_CANDIDATE*/
static int	assignment_candidate(t_list **token_list, int *i, int pos)
{
	int		start;
	int		end;
	//int		len;
	char	*str_token;
	t_token	*token;

	token = (t_token *)(ft_lstpos(*token_list, *i)->content);
	str_token = token->value;
	//len = (int) ft_strlen(str_token);
	start = find_start_assignment(str_token, pos);
	if (start != -1)
	{
		end = find_end_assignment(str_token, pos + 1) - 1;
		if (end != -1)
		{
			if (add_nodes(token_list, i, start, end) == NULL)
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

/*Funcio que encuentra todos los TOKEN_ASSIGNMENT_CANDIDATE
t_list	**assignment_divider(t_list **token_list, char *str)
{
	int		i;
	int		assignment;
	char	*str_token;
	t_list	*lst_token_word;

	lst_token_word = create_node(str, 0, ft_strlen(str) - 1, 0);
	if (lst_token_word == NULL)
		return (error_list(token_list));
	ft_lstadd_back(token_list, lst_token_word);
	str_token = ((t_token *)(lst_token_word->content))->value;
	i = find_next_equal(str_token, 0);
	while (i > 0)
	{
		assignment = assignment_candidate(token_list, i);
		if (assignment == -1)
			return (error_list(token_list));
		else if (assignment == 0)
			i = find_next_equal(str_token, i + 1);
		else
		{
			str_token = ((t_token *)(ft_lstlast(*token_list)->content))->value;
			i = find_next_equal(str_token, 0);
		}
	}
	return (token_list);
}*/

//tengo que reparar esta parte. Lo que tiene que pasar es que reciba la lista en lugar del string.
//debe mirar en cada token a ver si es TOKEN_WORD
//en caso de ser TOKEN_WORD buscar los posible assignment 
//
//Lo que esta hecho hasta ahora es un apano que deberia ser corregido
//Lo que esta arriba comantado es como estaba originalmente. Funciona pero no se puede introducir el parentheses_divider

/*Funcion que introduce new en token list en la pos i
static int	replace_list(t_list **token_list, t_list **new_token_list, int *i)
{
	t_list	*lst_del;
	t_list	*lst_aux;

	lst_del = ft_lstpos(*token_list, *i);
	if (*i = 0)
	{
		lst_aux = ft_lstpos(*token_list, 1);
		(ft_lstlast(new_token_list))->next = lst_aux;
		token_list = new_token_list;

	}
}*/

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
