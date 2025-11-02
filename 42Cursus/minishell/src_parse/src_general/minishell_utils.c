/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:45:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/28 02:47:47 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que calcula la cantidad de strings que hay en un string doble*/
int	doublestr_len(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/*Funcion que calcula la cantidad de strings de un string doblen en un token*/
int	calculate_strlen(t_token_ast *token)
{
	int		len;
	char	**str;

	if (token == NULL)
		return (-1);
	str = token->value;
	len = doublestr_len(str);
	return (len);
}

/*Funcion que remplaza el la $VAR en posicion i por el new_str*/
int	replace_string(char **str, char *new_str, int command_len, int pos)
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
char	*get_command(char *str, int x)
{
	int		i;
	int		len;
	char	*command;

	i = x + 1;
	len = 0;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
	{
		i++;
		len++;
	}
	command = (char *) malloc ((len + 2) * sizeof(char));
	if (!command)
		return (NULL);
	ft_strlcpy(&command[0], &str[x], len + 2);
	len = ft_strlen(command);
	return (command);
}
