/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_divider.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:58:35 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/21 13:59:00 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona la creacion del TOKEN_WORD hasta el parentesis*/
static t_list	**start_list(t_list **token_list, char *str, int open)
{
	char	*str_token;
	t_token	*new_token;
	t_list	*new_node;

	str_token = (char *) malloc (sizeof(char) * (open + 2));
	new_token = (t_token *) malloc (sizeof (t_token));
	if (str_token == NULL || new_token == NULL)
	{
		free(str_token);
		free(new_token);
		return (NULL);
	}
	ft_strlcpy(str_token, str, open + 2);
	new_token->value = str_token;
	new_token->type = TOKEN_WORD;
	new_token->finished = 0;
	new_token->quote = 0;
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		delete_token(new_token);
		return (NULL);
	}
	ft_lstadd_back(token_list, new_node);
	return (token_list);
}

/*Funcion que gestiona la creacion de la lista del contenido entre parentesis*/
static t_list	**par_list(t_list **lst, char **env, char *str, t_list **tmp)
{
	int		open;
	int		close;
	char	*str_token;
	t_list	**new_token_list;

	open = find_next_parenthesis(str);
	close = close_parenthesis(str, open);
	str_token = (char *) malloc (sizeof(char) * (close - open));
	if (!str_token)
		return (NULL);
	ft_strlcpy(str_token, &str[open + 1], close - open);
	new_token_list = lexer(str_token, env, tmp);
	if (!new_token_list)
	{
		free(str_token);
		return (NULL);
	}
	ft_lstadd_back(lst, *new_token_list);
	free(new_token_list);
	free(str_token);
	return (lst);
}

/*Funcion que gestiona la creacion de la nueva token list*/
static t_list	**create_new(char *str, char **env, t_list **tmp_var)
{
	t_list	**new_token_list;

	new_token_list = (t_list **) malloc (sizeof(t_list *));
	if (!new_token_list)
		return (NULL);
	*new_token_list = NULL;
	new_token_list = paren_divider(new_token_list, str, env, tmp_var);
	if (!new_token_list)
		return (NULL);
	return (new_token_list);
}

/*Funcion que gestiona la creacion del TOKEN_WORD despues del parentesis*/
static t_list	**end_list(t_list **lst, char **env, char *str, t_list **tmp)
{
	char	*str_token;
	t_list	**new_token_list;
	int		open;
	int		close;
	int		len;

	open = find_next_parenthesis(str);
	close = close_parenthesis(str, open);
	len = (int) ft_strlen(str);
	str_token = (char *) malloc (sizeof(char) * (len - close + 1));
	if (!str_token)
		return (NULL);
	ft_strlcpy(str_token, &str[close], len - close + 1);
	new_token_list = create_new(str_token, env, tmp);
	if (!new_token_list)
	{
		free(str_token);
		return (NULL);
	}
	ft_lstadd_back(lst, *new_token_list);
	free(new_token_list);
	free(str_token);
	return (lst);
}

/*Funcion que llama a lexer de forma recursiva para manejar los parentesis*/
t_list	**paren_divider(t_list **lst, char *str, char **env, t_list **tmp)
{
	int		open;
	int		close;

	open = find_next_parenthesis(str);
	if (open == -1)
	{
		create_unique_node(lst, str);
		return (lst);
	}
	close = close_parenthesis(str, open);
	if (close == -1)
		return (error_list(lst));
	if (start_list(lst, str, open) == NULL)
		return (error_list(lst));
	if (par_list(lst, env, str, tmp) == NULL)
		return (error_list(lst));
	if (end_list(lst, env, str, tmp) == NULL)
		return (error_list(lst));
	return (lst);
}
