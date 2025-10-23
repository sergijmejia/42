/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:40:30 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 14:12:26 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona cuando la variabl no es $?*/
static char	*saved_string(char *command, char **env, t_list **tmp_var)
{
	char	*new_str;

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
	return (new_str);
}

/*Funcion que gestiona una la sexpansion de una variable en el heredoc*/
static int	var_exp_heredoc(char **str, int pos, char **env, t_list **tmp_var)
{
	int		command_len;
	char	*new_str;
	char	*command;

	if ((*str)[pos + 1] == '?')
	{
		command_len = 2;
		new_str = ft_itoa(g_exit_status);
	}
	else
	{
		command = get_command(*str, pos);
		if (command == NULL)
			return (-1);
		command_len = ft_strlen(command);
		new_str = saved_string(command, env, tmp_var);
		free(command);
	}
	if (new_str == NULL)
		return (-1);
	pos = replace_string(str, new_str, command_len, pos);
	free(new_str);
	return (pos);
}

/*Funcion que expande las variables en una str*/
static char	*simple_var_expansion(char *str, char **env, t_list **tmp_var)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str)[i] == '$' && (str)[i + 1] != '\n')
		{
			if ((str)[i + 1] != '$')
			{
				if (ft_isalpha((str)[i + 1]) || (str)[i + 1] == '_')
				{
					i = var_exp_heredoc(&str, i, env, tmp_var);
					if (i == -1)
						return (NULL);
				}
				else
					i++;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (str);
}

/*Funcion que expande variables en heredoc*/
char	**heredoc_var_expansion(char **str, t_aux *aux, int pos)
{
	int		i;
	int		quote;
	char	**env;
	t_list	**tmp_var;
	t_list	**lst;

	env = aux->env;
	tmp_var = aux->tmp_var;
	lst = aux->token_list;
	quote = ((t_token_ast *)((ft_lstpos(*lst, pos))->content))->quote;
	if (quote == 1)
		return (str);
	i = 0;
	while (str[i])
	{
		str[i] = simple_var_expansion(str[i], env, tmp_var);
		if (str[i] == NULL)
			return (free_str(str));
		i++;
	}
	return (str);
}

/*Funcion que crea el heredoc_str*/
char	**heredoc_size(int *fd)
{
	char	*str;
	int		size;
	char	**heredoc_str;

	size = 0;
	str = get_next_line(*fd);
	while (str != NULL)
	{
		size++;
		free(str);
		str = get_next_line(*fd);
	}
	close(*fd);
	*fd = open(".tmp_minishell", O_RDONLY);
	if (*fd == -1)
		return (NULL);
	heredoc_str = (char **) malloc ((size + 2) * sizeof(char *));
	if (heredoc_str == NULL)
	{
		close(*fd);
		return (NULL);
	}
	return (heredoc_str);
}
