/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_lex_par.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:37:50 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/18 17:08:41 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que duplica un token*/
static t_token	*duplicate_token(t_token *token)
{
	t_token	*new_token;
	char	*str;

	new_token = (t_token *) malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	str = ft_strdup(token->value);
	if (!str)
	{
		free(new_token);
		return (NULL);
	}
	new_token->value = str;
	new_token->type = token->type;
	new_token->finished = token->finished;
	return (new_token);
}

/*Funcion que crea un nuevo token de transicion*/
static  t_token_ast	*create_new_tr_token(char **str, t_type_lexer type, int w)
{
	t_token_ast	*new_token;
	t_type_tr	tr_type;

	new_token = (t_token_ast *) malloc (sizeof(t_token_ast));
	if (!new_token)
		return (NULL);
	new_token->value = str;
	if (type == 0)
		tr_type = 0;
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

/*Funcion que crea el nodo de transcion para los caracteres especiales*/
static t_list	*special_node(t_list **token_list, int pos, t_type_lexer type)
{
	t_list		*new_node;
	t_token_ast	*new_token;
	char		**str;
	char		*str_token;

	str_token = ((t_token *)((ft_lstpos(*token_list, pos))->content))->value;
	str = (char **) malloc (2 * sizeof(char *));
	if (!str)
		return (NULL);
	str[0] = ft_strdup(str_token);
	str[1] = NULL;
	new_token = create_new_tr_token(str, type, 0);
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
		return(NULL);
	}
	return (new_node);
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
		str[i] = ft_strdup(str_lst);
		if (!str[i])
		{
			free_str(str);
			free(str);
			return (NULL);
		}
		i++;
		start++;
	}
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
		if (!((type >= 0 && type <=3) ||  type == 16))
			break ;
		(*pos)++;
	}
	str = create_str_command(lst, start, *pos);
	if(!str)
		return (NULL);
	return (str);
}

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
		if (!((type >= 0 && type <=3) ||  type == 16))
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

/*Funcion que crea el nodo de transicion para los comandos*/
static t_list	*command_node(t_list **token_list, int *pos)
{
	char		**str;
	int			wildcard;
	t_token_ast	*new_token;
	t_list		*new_node;

	wildcard = check_wildcard(token_list, *pos);
	str = str_command(token_list, pos);
	new_token = create_new_tr_token(str, 0, wildcard);
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
		return(NULL);
	}
	return (new_node);
}

/*Funcion que hace crea la lista tr_lexer_parser*/
static t_list	**make_transition(t_list **token_list)
{
	t_list			**new_lst;
	t_list			*new_node;
	t_type_lexer	type;
	int				pos;
	int				len;

	pos = 0;
	len = ft_lstsize(*token_list);
	new_lst = (t_list **) malloc (sizeof(t_list *));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	while (pos < len)
	{
		type = ((t_token *)((ft_lstpos(*token_list, pos))->content))->type;
		if ((type >= 4 && type <= 8) || (type >= 10 && type <= 14))
		{
			new_node = special_node(token_list, pos, type);
			pos++;
		}
		else
			new_node = command_node(token_list, &pos);
		if (!new_node)
			error_tr(new_lst);
		ft_lstadd_back(new_lst, new_node);
	}
	ft_lstclear(token_list, delete_token);
	*token_list = *new_lst;
	free(new_lst);
	return (token_list);
}

/*Funcion que crea la lista hasta '('*/
static t_list	**lst_until_open(t_list **token_list, int open)
{
	int	i;
	t_list	**new_lst;
	t_list	*new_node;
	t_token	*new_token;
	t_token	*token;

	i = 0;
	new_lst = (t_list **) malloc (sizeof(t_list*));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	while (i <= open)
	{
		token = (t_token *)((ft_lstpos(*token_list, i))->content);
		new_token = duplicate_token(token);
		if (!new_token)
			return (error_list(new_lst));
		new_node = ft_lstnew(new_token);
		if (!new_node)
		{
			delete_token(new_token);
			return (error_list(new_lst));
		}
		ft_lstadd_back(new_lst, new_node);
		i++;
	}
	return (new_lst);
}

/*Funcion que crea la lista de transicion hasta '('*/
static t_list	**start_list(t_list **token_list, t_list **new_list, int open)
{
	t_list	**lst_aux;

	lst_aux = lst_until_open(token_list, open);
	if (!lst_aux)
		return (NULL);
	if (make_transition(lst_aux) == NULL)
	{
		error_list(lst_aux);
		free(lst_aux);
		return (NULL);
	}
	ft_lstadd_back(new_list, *lst_aux);
	free(lst_aux);
	return (new_list);
}

/*Funcion que crea la lista dentro de los parentesis correspondientes*/
static t_list	**lst_inside_parentheses(t_list **lst, int open, int close)
{
	t_list	**new_lst;
	t_list	*new_node;
	t_token	*new_token;
	t_token	*token;

	new_lst = (t_list **) malloc (sizeof(t_list*));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	while (open < close)
	{
		token = (t_token *)((ft_lstpos(*lst, open))->content);
		new_token = duplicate_token(token);
		if (!new_token)
			return (error_list(new_lst));
		new_node = ft_lstnew(new_token);
		if (!new_node)
		{
			delete_token(new_token);
			return (error_list(new_lst));
		}
		ft_lstadd_back(new_lst, new_node);
		open++;
	}
	return (new_lst);	
}

/*Funcion que encuentra la pos del ')' correspondiente*/
static int	pos_close(t_list **token_list, int open)
{
	t_type_lexer	type;
	t_list			*node;
	int				count;

	count = 1;
	open++;
	node = ft_lstpos(*token_list, open);
	while (node && count > 0)
	{
		type = ((t_token *)(node->content))->type;
		if (type == TOKEN_RPAREN)
			count++;
		if (type == TOKEN_LPAREN)
			count--;
		if (count == 0)
			return (open);
		open++;
		node = ft_lstpos(*token_list, open);
	}
	return (-1);
}

/*Funcion que crea la lista de transicion dentro del parentesis*/
static t_list	**parentheses_list(t_list **token_list, t_list **new, int open)
{
	t_list	**lst_aux;
	int		close;

	close = pos_close(token_list, open);
	if (close == -1)
		return (NULL);
	lst_aux = lst_inside_parentheses(token_list, open + 1, close);
	if (!lst_aux)
		return (NULL);
	if (transition_lex_par(lst_aux) == NULL)
	{
		free(lst_aux);
		return (NULL);
	}
	ft_lstadd_back(new, *lst_aux);
	free(lst_aux);
	return (new);

}

/*Funcion que crea la lista desde '('*/
static t_list	**lst_until_end(t_list **token_list, int close)
{
	t_list	**new_lst;
	t_list	*new_node;
	t_token	*new_token;
	t_token	*token;
	int		len;

	new_lst = (t_list **) malloc (sizeof(t_list*));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	len = ft_lstsize(*token_list);
	while (close < len)
	{
		token = (t_token *)((ft_lstpos(*token_list, close))->content);
		new_token = duplicate_token(token);
		if (!new_token)
			return (error_list(new_lst));
		new_node = ft_lstnew(new_token);
		if (!new_node)
			return (error_token(new_lst, new_token));
		ft_lstadd_back(new_lst, new_node);
		close++;
	}
	return (new_lst);
}

/*Funcion que crea la lista de transicion desde ')' hasta el final*/
static t_list	**end_list(t_list **token_list, t_list **new_list, int close)
{
	t_list			**lst_aux;
	t_list			*new_node;
	t_type_lexer	type;

	lst_aux = lst_until_end(token_list, close + 1);
	if (!lst_aux)
		return (NULL);
	type = ((t_token *)((ft_lstpos(*token_list, close))->content))->type;
	new_node = special_node(token_list, close, type);
	if (!new_node)
			error_list(lst_aux);
	ft_lstadd_back(new_list, new_node);
	if (transition_lex_par(lst_aux) == NULL)
	{
		free(lst_aux);
		return (NULL);
	}
	ft_lstadd_back(new_list, *lst_aux);
	free(lst_aux);
	return (new_list);
}

/*Funcion que encuentra el primer '(' de la lista*/
static int	find_open_parenthesis(t_list **open_list)
{
	t_token			*token;
	t_type_lexer	type;
	int				len;
	int				i;

	i = 0;
	len = ft_lstsize(*open_list);
	while (i < len)
	{
		token = (t_token *)((ft_lstpos(*open_list, i))->content);
		type = token->type;
		if (type == TOKEN_RPAREN)
			return (i);
		i++;
	}
	return (-1);
}

/*Funcion que encuentra el ')' correspondiente de la lista*/
static int	find_close_parenthesis(t_list **close_list, int	pos)
{
	t_token			*token;
	t_type_lexer	type;
	int				count;
	int				len;

	count = 1;
	len = ft_lstsize(*close_list);
	while (pos < len && count >= 0)
	{
		token = (t_token *)((ft_lstpos(*close_list, pos))->content);
		type = token->type;
		if (type == TOKEN_RPAREN)
			count++;
		else if(type == TOKEN_LPAREN)
		{
			count--;
			if (count == 0)
				return (pos);
		}
		pos++;
	}
	return (-1);
}

/*Funcion que llama a transicion lexer/parser de forma recursiva
para menejar los parentesis*/
t_list	**transition_lex_par(t_list **token_list)
{
	int		open;
	int		close;
	t_list	**new_lst;

	open = find_open_parenthesis(token_list);
	if (open == -1)
	{
		make_transition(token_list);
		return (token_list);
	}
	close = find_close_parenthesis(token_list, open + 1);
	if (close == -1)
		return (error_list(token_list));
	new_lst = (t_list **) malloc (sizeof(t_list *));
	if (!new_lst)
		return (error_list(token_list));
	*new_lst = NULL;
	if (start_list(token_list, new_lst, open) == NULL)
	{
		error_tr(new_lst);
		free(new_lst);
		return (error_list(token_list));
	}
	if (parentheses_list(token_list, new_lst, open) == NULL)
	{
		error_tr(new_lst);
		free(new_lst);
		return (error_list(token_list));
	}
	if (end_list(token_list, new_lst, close) == NULL)
	{
		error_tr(new_lst);
		free(new_lst);
		return (error_list(token_list));
	}
	ft_lstclear(token_list, delete_token);
	*token_list = *new_lst;
	free(new_lst);
    return (token_list);
}
