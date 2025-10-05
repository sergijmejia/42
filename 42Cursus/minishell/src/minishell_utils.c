/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:45:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/02 16:33:53 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que calcula la cantidad de strings que hay en un string doble*/
int	calculate_strlen(t_token_ast *token)
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

/*Funcion que duplica un token_ast*/
t_token_ast	*duplicate_token_tr(t_token_ast *token)
{
	t_token_ast	*new_token;
	char		**str;
	char		**new_str;
	int			len;
	int			i;

	len = calculate_strlen(token);
	if (len == -1)
		return (NULL);
	str = token->value;
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
