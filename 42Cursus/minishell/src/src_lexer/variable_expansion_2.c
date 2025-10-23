/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:53:44 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/23 13:18:37 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que gestiona cuando el segundo caracter != de $ y de ?*/
static char	*second_exp_var_2(char *str, int i, int *command_len, t_aux *aux)
{
	char	*command;
	char	*new_str;

	command = get_command(str, i);
	if (command == NULL)
		return (NULL);
	*command_len = ft_strlen(command);
	new_str = find_var((&command[1]), aux->tmp_var);
	if (new_str == NULL)
	{
		free(command);
		return (NULL);
	}
	if (new_str[0] == '\0')
	{
		free(new_str);
		new_str = ft_getenv(aux->env, &command[1]);
	}
	free(command);
	return (new_str);
}

/*Funcion que gestiona cuando el segundo caracter != de $*/
static char	*second_exp_var(char *str, int i, int *command_len, t_aux *aux)
{
	char	*new_str;

	if (str[i + 1] == '?')
	{
		*command_len = 2;
		new_str = ft_itoa(g_exit_status);
	}
	else
		new_str = second_exp_var_2(str, i, command_len, aux);
	return (new_str);
}

/*Funcion que gestiona el bucle de while(str[i])*/
static t_list	**expandible_string_loop(t_aux *aux, int *i, char **str)
{
	t_list	**lst;
	char	*new_str;
	int		command_len;

	lst = aux->token_list;
	if ((*str)[*i] == '$' && (*str)[*i + 1] != '\0')
	{
		if ((*str)[*i + 1] != '$')
		{
			new_str = second_exp_var(*str, *i, &command_len, aux);
			if (new_str == NULL)
				return (NULL);
			*i = replace_string(str, new_str, command_len, *i);
			free(new_str);
			if (*i == -1)
				return (NULL);
			((t_token *)((ft_lstpos(*lst, aux->x))->content))->value = *str;
		}
		else
			(*i)++;
	}
	else
		(*i)++;
	return (aux->token_list);
}

static int	quote_manager(char *str, int *double_quote, int i)
{
	if (str[i] == '\"')
	{
		if (*double_quote == 0)
			*double_quote = 1;
		else
			*double_quote = 0;
		i++;
	}
	else if ((str[i] == '\'') && (*double_quote == 0))
	{
		i = next_quote(str, i);
		i++;
	}
	return (i);
}

/*Funcion que gestiona la expansion de varables en TOKEN_EXPANDIBLE_STRINGS*/
t_list	**exp_string(t_list **lst, char **env, int x, t_list **tmp_var)
{
	int		i;
	char	*str;
	t_aux	*aux;
	int		double_quote;

	i = 0;
	aux = (t_aux *) malloc (sizeof(t_aux));
	aux->token_list = lst;
	aux->tmp_var = tmp_var;
	aux->env = env;
	aux->x = x;
	str = ((t_token *)((ft_lstpos(*lst, x))->content))->value;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i = quote_manager(str, &double_quote, i);
		else if (expandible_string_loop(aux, &i, &str) == NULL)
		{
			free(aux);
			return (NULL);
		}
	}
	free(aux);
	return (lst);
}
