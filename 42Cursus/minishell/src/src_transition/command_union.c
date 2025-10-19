/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_union.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:42:13 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/17 12:21:37 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que junta los str de new y de token*/
static char	**str_nodes(t_token_ast *n, t_token_ast *t, int len_n, int len_t)
{
	char	**str;
	int		i;

	str = (char **) malloc ((len_n + len_t + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len_n)
	{
		str[i] = ft_strdup((n->value)[i]);
		if (str[i] == NULL)
			return (free_str(str));
		i++;
	}
	i = 0;
	while (i < len_t)
	{
		str[i + len_n] = ft_strdup((t->value)[i]);
		if (str[i + len_n] == NULL)
			return (free_str(str));
		i++;
	}
	str[len_n + len_t] = NULL;
	return (str);
}

/*Funcion que agrega el str del token en pos a new_token*/
/*Si el str de token es vacio lo descarta*/
static t_token_ast	**join_nodes(t_token_ast **new, t_token_ast *token)
{
	int		len_new;
	int		len_token;
	char	**str;

	if (*new == NULL)
	{
		*new = duplicate_token_tr(token);
		return (new);
	}
	len_new = calculate_strlen(*new);
	len_token = calculate_strlen(token);
	if ((len_token == 1) && (ft_strlen((token->value)[0]) == 0))
		return (new);
	if (len_new == -1 || len_token == -1)
		return (NULL);
	str = str_nodes(*new, token, len_new, len_token);
	if (str == NULL)
		return (NULL);
	free_str((*new)->value);
	(*new)->value = str;
	if (token->wildcard)
		(*new)->wildcard = 1;
	return (new);
}

/*Funcion que gestiona el loop de changed_token*/
static t_token_ast	**changed_token_loop(t_token_ast **new, t_token_ast *token)
{
	if (token->type == 0)
	{
		if (join_nodes(new, token) == NULL)
			return (NULL);
	}
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
		if (changed_token_loop(&new_token, token) == NULL)
		{
			delete_token_ast(new_token);
			return (NULL);
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
/*Es el ultimo de los special seguidos que se encuentra, no */
/*el ultimo de la lista*/
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

/*Funcion que gestiona el bucle de replace_node*/
static t_list	**replace_node_loop(t_list **lst, int *pos, int *pos_special)
{
	t_type_tr	type;
	t_list		*aux;
	t_list		*aux2;

	aux = (ft_lstpos(*lst, *pos));
	if (aux == NULL)
		return (NULL);
	type = ((t_token_ast *)(aux->content))->type;
	if (type == 0)
	{
		aux2 = ft_lstpos(*lst, *pos - 1);
		if (aux2 == NULL)
			return (NULL);
		aux2->next = aux->next;
		ft_lstdelone(aux, delete_token_ast);
		*pos_special = special_token(lst, *pos);
	}
	else
		(*pos)++;
	return (lst);
}

/*Funcion que elimina todos los nodos que se han agrupado en new_node*/
static t_list	**replace_node(t_list **lst, t_list *new_node, int *pos)
{
	int			pos_special;
	t_list		*aux;

	aux = (ft_lstpos(*lst, *pos));
	if (aux == NULL)
		return (NULL);
	new_node->next = (ft_lstpos(*lst, *pos))->next;
	if (*pos > 0)
		(ft_lstpos(*lst, *pos - 1))->next = new_node;
	else
		*lst = new_node;
	ft_lstdelone(aux, delete_token_ast);
	(*pos)++;
	pos_special = special_token(lst, *pos);
	while (*pos < pos_special)
	{
		if (replace_node_loop(lst, pos, &pos_special) == NULL)
			return (NULL);
	}
	return (lst);
}

/*Funcion que gestiona el bucle de command_union*/
static t_list	**command_union_loop(t_list **lst, t_type_tr type, int *pos)
{
	t_token_ast	*new_token;
	t_list		*new_node;

	if (type == 0)
	{
		new_token = changed_token(lst, *pos);
		if (new_token == NULL)
			return (error_tr(lst));
		new_node = ft_lstnew(new_token);
		if (new_node == NULL)
		{
			delete_token_ast(new_token);
			return (error_tr(lst));
		}
		if (replace_node(lst, new_node, pos) == NULL)
		{
			delete_token_ast(new_token);
			free(new_node);
			return (error_tr(lst));
		}
	}
	return (lst);
}

/*Funcion para unir comandos entre caracteres especiales*/
t_list	**command_union(t_list **token_list)
{
	int			i;
	t_list		*node;
	t_token_ast	*token;
	t_type_tr	type;

	i = 0;
	node = *token_list;
	while (node != NULL)
	{
		token = (t_token_ast *)(node->content);
		type = token->type;
		if (command_union_loop(token_list, type, &i) == NULL)
			return (error_tr(token_list));
		i++;
		node = ft_lstpos(*token_list, i);
	}
	return (token_list);
}
