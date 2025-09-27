/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_union.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:42:13 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/25 16:42:57 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que calcula la cantidad de strings que hay en un string doble*/
static int	calculate_strlen(t_token_ast *token)
{
	int		len;
	char	**str;

	if (token == NULL)
		return (-1);
	str = token->value;
	len = 0;
	while (str[len])
		len++;
	return (len);
}

/*Funcion que duplica un token*/
static t_token_ast	*duplicate_token_tr(t_token_ast *token)
{
	t_token_ast	*new_token;
	char		**str;
	char		**new_str;
	int			len;
	int			i;

	len = calculate_strlen(token);
	if (len == -1)
		return (NULL);
	str = (char **)(token->value);
	new_str = (char	**) malloc ((len + 1) * sizeof(char *));
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

/*Funcion que agrega el str del token en pos a new_token*/
static t_token_ast	**join_nodes(t_token_ast **new, t_token_ast *token)
{
	int		len_new;
	int		len_token;
	int		i;
	char	**str;
	
	if (*new == NULL)
	{
		*new = duplicate_token_tr(token);
		return (new);
	}
	len_new = calculate_strlen(*new);
	len_token = calculate_strlen(token);
	if (len_new == -1 || len_token == -1)
		return (NULL);
	str = (char **) malloc ((len_new + len_token + 1) * sizeof(char	*));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len_new)
	{
		str[i] = ft_strdup(((*new)->value)[i]);
		if (str[i] == NULL)
		{
			free_str(str);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < len_token)
	{
		str[i + len_new] = ft_strdup((token->value)[i]);
		if (str[i + len_new] == NULL)
		{
			free_str(str);
			return (NULL);
		}
		i++;
	}
	str[len_new + len_token] = NULL;
	free_str((*new)->value);
	(*new)->value = str;
	if (token->wildcard)
		(*new)->wildcard = 1;
	return (new);
}

/*Funcion que crea el nuevo nodo de union de todos los word*/
static t_token_ast	*changed_token(t_list **token_list, int pos)
{
	t_token_ast	*token;
	t_token_ast	*new_token;
	t_list		*node;

	new_token = NULL;
	node = ft_lstpos(*token_list, pos);
	if (node == NULL)
		return (NULL);
	token = (t_token_ast *)(node->content);
	while (token->type != 1 && (token->type < 6 || token->type == 11))
	{
		if (token->type == 0)
		{
			if (join_nodes(&new_token, token) == NULL)
			{
				delete_token_ast(new_token);
				return (NULL);
			}
		}
		pos++;
		node = ft_lstpos(*token_list, pos);
		if (node == NULL)
			break ;
		token = (t_token_ast *)(node->content);
	}
	return (new_token);
}

/*Funcion que devuelve la posicion del ultimo token special*/
/*Es el ultimo de los special seguidos que se encuentra, no el ultimo de la lista*/
static int	special_token(t_list **token_list, int pos)
{
	t_type_tr	type;
	int			size;

	size = ft_lstsize(*token_list);
	while (pos < size)
	{
		type = ((t_token_ast *)((ft_lstpos(*token_list, pos))->content))->type;
		if (type == 11 || (type < 6 && type != 1))
				pos++;
		else
			break ;
	}
	if (pos == size)
		return (pos);
	while (pos < size)
	{
		type = ((t_token_ast *)((ft_lstpos(*token_list, pos))->content))->type;
		if (type == 1 || (type >= 6 && type <= 10))
			pos++;
		else 
			break ;
	}
	return (pos - 1);
}

/*Funcion que elimina todos los nodos que se han agrupado en new_node*/
t_list	**replace_node(t_list **lst, t_list *new_node, int *pos)
{
	int			pos_special;
	t_type_tr	type;
	t_list		*aux;

	new_node->next = (ft_lstpos(*lst, *pos))->next;
	aux = (ft_lstpos(*lst, *pos));
	if (*pos > 0)
		(ft_lstpos(*lst, *pos - 1))->next = new_node;
	else
		*lst = new_node;
	ft_lstdelone(aux, delete_token_ast);
	(*pos)++;
	pos_special = special_token(lst, *pos);
	while (*pos < pos_special)
	{
		type = ((t_token_ast *)((ft_lstpos(*lst, *pos))->content))->type;
		if (type == 0)
		{
			aux = (ft_lstpos(*lst, *pos));
			(ft_lstpos(*lst, *pos - 1))->next = aux->next;
			ft_lstdelone(aux, delete_token_ast);
			pos_special = special_token(lst, *pos);
		}
		else
			(*pos)++;
	}
	return (lst);
}

/*Funcion para unir comandos entre caracteres especiales*/
t_list	**command_union(t_list **token_list)
{
	int			i;
	t_list		*node;
	t_list		*new_node;
	t_token_ast	*token;
	t_token_ast	*new_token;
	t_type_tr	type;

	i = 0;
	node = *token_list;
	while (node != NULL)
	{
		token = (t_token_ast *)(node->content);
		type = token->type;
		if (type == 0)
		{
			new_token = changed_token(token_list, i);
			if (new_token == NULL)
				return (error_tr(token_list));
			new_node = ft_lstnew(new_token);
			if (new_node == NULL)
			{
				delete_token_ast(new_token);
				return (error_tr(token_list));
			}
			if (replace_node(token_list, new_node, &i) == NULL)
			{
				delete_token_ast(new_token);
				free(new_node);
				return (error_tr(token_list));
			}
		}
		i++;
		node = ft_lstpos(*token_list, i);
	}
	return (token_list);
}
