/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses_balance.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:37:57 by smejia-a          #+#    #+#             */
/*   Updated: 2025/07/17 16:35:12 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que cuenta los caracteres hasta las siguientes comillas*/
static int	number_of_char_to_next_quote(char *str)
{
	int		pos;
	char	c;

	pos = 1;
	c = *str;
	while (str[pos])
	{
		if (str[pos] == c)
			return (pos);
		pos++;
	}
	return (0);
}

/*Funcion que verifica correcta cantidad y distribucion de parentesis*/
int	check_parentheses_balance(char *str)
{
	int	parenthesis;
	int	pos;

	parenthesis = 0;
	while (*str)
	{
		if (*str == '(')
			parenthesis++;
		else if (*str == ')')
			parenthesis--;
		if (parenthesis < 0)
			return (1);
		if (*str == '\'' || *str == '\"')
		{
			pos = number_of_char_to_next_quote(str);
			if (pos == 0)
				return (1);
			str = str + pos;
		}
		str++;
	}
	if (parenthesis == 0)
		return (0);
	return (1);
}
