/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:36:48 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/13 16:18:15 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que remplaza el la $VAR en posicion i por el new_str*/
static int	replace_string(char **str, char *new_str, int command_len, int pos)
{
	int		len;
	int		div;
	int		len_str;
	int		new_len;
	char	*replace_str;

	new_len = (int)(ft_strlen(new_str));
	len = (int)(new_len + ft_strlen(*str) - command_len);
	replace_str = malloc(len + 1);
	if (!replace_str)
		return (-1);
	replace_str[len] = '\0';
	div = pos + command_len;
	len_str = (int)(ft_strlen(*str)) - pos - command_len;
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
	{
		write(1, "bucle\n", 6);
		write(1, &str[i], 1);
		i++;
		len++;
	}
	command = (char *) malloc ((len + 2) * sizeof(char));
	if (!command)
		return (NULL);
	ft_strlcpy(&command[0], &str[x], len + 2);
	len = ft_strlen(command);
	write(1, "el command es: ", 15);
	write(1, command, len + 1);
	write(1, "\n", 1);
	return (command);
}

/*Funcion que gestiona cuando el segundo caracter != de $*/
static char *second_exp_var(char *str, int i, char **env, t_list **tmp_var, int *command_len)
{
	char	*command;
	char	*new_str;
	
	if (str[i + 1] == '?')
	{
		*command_len = 2;
		new_str = ft_itoa(g_exit_status);
	}
	else
	{
		command = get_command(str, i);
		if (command == NULL)
			return (NULL);
		*command_len = ft_strlen(command);
		new_str = find_var((&command[1]), tmp_var);
		if (new_str == NULL)
		{
			free(command);
			return (NULL);
		}
		if (new_str[0] == '\0')
		{
			free(new_str);
			new_str = ft_getenv(env, &command[1]);
		}
		free(command);
	}
	return (new_str);
}

/*Funcion que gestiona la expansion de varables en TOKEN_EXPANDIBLE_STRINGS*/
static t_list	**expandible_string(t_list **token_list, char **env, int x, t_list **tmp_var)
{
	int		i;
	int		command_len;
	char	*str;
	//char	*command;
	char	*new_str;

	i = 0;
	str = ((t_token *)((ft_lstpos(*token_list, x))->content))->value;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			if (str[i + 1] != '$')
			{
				/*if (str[i + 1] == '?')
				{
					command_len = 2;
					new_str = ft_itoa(g_exit_status);
				}
				else
				{
					command = get_command(str, i);
					if (command == NULL)
						return (NULL);
					command_len = ft_strlen(command);
					new_str = find_var((&command[1]), tmp_var);
					if (new_str == NULL)
					{
						free(command);
						return (NULL);
					}
					if (new_str[0] == '\0')
					{
						free(new_str);
						new_str = ft_getenv(env, &command[1]);
					}
					free(command);
				}*/
				new_str = second_exp_var(str, i, env, tmp_var, &command_len);
				if (new_str == NULL)
					return (NULL);
				i = replace_string(&str, new_str, command_len, i);
				free(new_str);
				if (i == -1)
					return (NULL);
				((t_token *)((ft_lstpos(*token_list, x))->content))->value = str;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (token_list);
}

/*Funcion que gestiona la exansion de variables*/
t_list	**variable_expansion(t_list **token_list, char **env, t_list **tmp_var)
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
			if(expandible_string(token_list, env, i, tmp_var) == NULL)
				return (error_list(token_list));
		}
		else if (token->type == TOKEN_EXPANDIBLE_STRINGS && token->finished == 0)
		{
			if (expandible_string(token_list, env, i, tmp_var) == NULL)
				return (error_list(token_list));
		}
		else if (token->type == TOKEN_ASSIGNMENT_CANDIDATE && token->finished == 0)
		{
			write(1, "pasa 1", 6);
			if (expandible_string(token_list, env, i, tmp_var) == NULL)
				return (error_list(token_list));
		}
		i++;
		lst = ft_lstpos(*token_list, i);
	}
	return (token_list);
}
