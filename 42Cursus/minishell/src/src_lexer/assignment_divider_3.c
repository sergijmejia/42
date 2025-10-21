/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_divider_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:24:19 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 11:47:13 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
t_list	**generate_nodes(t_list **lst, int i, int start, int end)
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
