/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:36:48 by smejia-a          #+#    #+#             */
/*   Updated: 2025/09/15 12:53:47 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que agrega una nueva lista new_list despues del nodo x de token_list*/
static void	replace_lstpos(t_list **token_list, t_list **new_list, int x)
{
	t_list	*last;
	t_list	*first;

	last = ft_lstlast(*new_list);
	last->next = ft_lstpos(*token_list, x + 1);
	ft_lstdel_pos(token_list, delete_token, x);
	if (x == 0)
		token_list = new_list;
	else
	{
		first = ft_lstpos(*token_list, x - 1);
		first->next = *new_list;
	}
}

/*Funcion que gestiona la expansion de variables en TOKEN_WORD*/
static t_list	**word(t_list **token_list, int x)
{
	int		len;
	char	*str;
	char	*new_str;
	t_list	*token;
	t_list	**new_lst;

	token = ft_lstpos(*token_list, x);
	str = ((t_token *)(token->content))->value;
	len = (int) ft_strlen(str);
	if (str[0] == '$' && len > 1)
	{
		if (len == 2 && str[1] == '?')
		{
			new_str = ft_itoa(g_exit_status);
			if (new_str == NULL)
				return (NULL);
		}
		else
		{
			new_str = getenv(&str[1]);
			if (new_str == NULL)
			{
				ft_lstdel_pos(token_list, delete_token, x);
				return (token_list);
			}
		}
		new_lst = lexer(new_str);
		free(new_str);
		if (new_lst == NULL)
			return (NULL);
		replace_lstpos(token_list, new_lst, x);
		free(new_lst);
	}
	return (token_list);
}

/*Funcion que remplaza el la $VAR en posicion i por el new_str*/
static int	replace_string(char **str, char *new_str, int command_len, int pos)
{
	int		len;
	int		div;
	int		len_str;
	int		new_len;
	char	*replace_str;

	new_len = (int) (ft_strlen(new_str));
	len = (int) (new_len + ft_strlen(*str) - command_len);
	replace_str = malloc(len + 1);
	if (!replace_str)
		return (-1);
	replace_str[len] = '\0';
	div = pos + command_len;
	len_str = (int) (ft_strlen(*str)) - pos - command_len;
	ft_strlcpy(&replace_str[0], *str, pos + 1);
	ft_strlcpy(&replace_str[pos], new_str, new_len + 1);
	ft_strlcpy(&replace_str[pos + new_len], &((*str)[div]), len_str + 1);
	free(*str);
	*str = replace_str;
	return (pos + new_len);
}

/*Funcion que devueve el comando*/
static char	*get_command(char *str, int x)
{
	int		i;
	int		len;
	char	*command;

	i = x + 1;
	len = 0;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
		len++;
	command = malloc (len + 2);
	if (!command)
		return (NULL);
	ft_strlcpy(&command[0], &str[i], len + 2);
	return (command);
}

/*Funcion que gestiona la expansion de varables en TOKEN_EXPANDIBLE_STRINGS*/
static t_list	**expandible_string(t_list **token_list, int x)
{
	int		i;
	int		command_len;
	char	*str;
	char	*command;
	char	*new_str;

	i = 0;
	str = ((t_token *)((ft_lstpos(*token_list, x))->content))->value;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			if (str[i + 1] == '?')
			{
				command_len = 2;
				new_str = ft_itoa(g_exit_status);
				if (new_str == NULL)
					return (NULL);
			}
			else
			{
				command = get_command(str, i);
				if (command == NULL)
					return (NULL);
				command_len = ft_strlen(command);
				new_str = getenv(&command[1]);
				free(command);
			}
			i = replace_string(&str, new_str, command_len, i);
			free(new_str);
			if (i == -1)
				return (NULL);
			((t_token *)((ft_lstpos(*token_list, x))->content))->value = str;
		}
		else
			i++;
	}
	return (token_list);
}

/*Funcion que gestiona la exansion de variables*/
t_list	**variable_expansion(t_list **token_list)
{
	int		i;
	t_token	*token;
	t_list	*lst;

	i = 0;
	lst = ft_lstpos(*token_list, i);
	while (lst != NULL)
	{
		token = (t_token *)(lst->content);
		if (token->type == TOKEN_WORD && token->finished == 0)
		{
			if (word(token_list, i) == NULL)
				return (error_list(token_list));
		}
		else if (token->type == TOKEN_EXPANDIBLE_STRINGS && token->finished == 0)
		{
			if (expandible_string(token_list, i) == NULL)
				return (error_list(token_list));
		}
		i++;
		lst = ft_lstpos(*token_list, i);
	}
	return (token_list);
}
