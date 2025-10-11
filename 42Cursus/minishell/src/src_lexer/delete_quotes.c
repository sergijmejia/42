/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:56:15 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/11 11:51:29 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que decide si se realiza una accion en la nueva string*/
static int	quote_char(char c, char *quote, int *inside)
{
	if (c == '\'' || c == '\"')
	{
		if (*inside == 0)
		{
			*quote = c;
			*inside = 1;
			return (1);
		}
		else
		{
			if (c == *quote)
			{
				*inside = 0;
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}

/*Funcion que cuenta la cantidad de caracteres entre las comillas*/
static int	count_new_len(char *str)
{
	int		inside;
	int		len;
	char	c;

	inside = 0;
	len = 0;
	c = '\0';
	while (*str)
	{
		if (quote_char(*str, &c, &inside) == 0)
			len++;
		/*if (*str == '\'' || *str == '\"')
		{
			if (inside == 0)
			{
				c = *str;
				inside = 1;
			}
			else
			{
				if (*str == c)
					inside = 0;
				else
					len++;
			}
		}
		else
			len++;*/
		str++;
	}
	return (len);
}

/*Funcion que copia caracter a caracter el contenido entre comillas*/
static char	*quote_str(char *str, int len)
{
	char	c;
	char	*new_str;
	int		count_str;
	int		count_new_str;
	int		inside;

	new_str = (char *) malloc (sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	new_str[len] = '\0';
	c = '\0';
	inside = 0;
	count_str = 0;
	count_new_str = 0;
	while (str[count_str])
    {
		if (quote_char(str[count_str], &c, &inside) == 0)
		{
			new_str[count_new_str] = str[count_str];
			count_new_str++;
		}
        /*if (str[count_str] == '\'' || str[count_str] == '\"')
        {
            if (inside == 0)
            {
                c = str[count_str];
                inside = 1;
            }
            else
            {
                if (str[count_str] == c)
                    inside = 0;
                else
                {
                    new_str[count_new_str] = str[count_str];
                    count_new_str++;
                }
            }
        }
        else
        {
            new_str[count_new_str] = str[count_str];
            count_new_str++;
        }*/
        count_str++;
    }
	return (new_str);
}

/*Funcion que crea el nuevo str que estaba contenido entre las comillas*/
static t_list	**quote_list(t_list **token_list, int pos)
{
	t_list	*lst;
	char	*str;
	char	*new_str;
	int		len;

	lst = ft_lstpos(*token_list, pos);
	if (lst == NULL)
		return (NULL);
	str = ((t_token *)(lst->content))->value;
	len = count_new_len(str);
	new_str = quote_str(str, len);
	free(str);
	if (new_str == NULL)
		return (NULL);
	((t_token *)(lst->content))->value = new_str;
	return (token_list);
}

/*Funcion encaragada de eliminar las comillas de los TOKEN_STRING_LITERAL (2),
TOKEN_EXPANDIBLE_STRINGS (3), TOKEN_REDIRECTION_WORD (17)*/
t_list	**delete_quotes(t_list **token_list)
{
	int		i;
	int		len;
	t_list	*token_list_aux;
	t_token	*token;

	i = 0;
	len = ft_lstsize(*token_list);
	while (i < len)
	{
		token_list_aux = ft_lstpos(*token_list, i);
		token = (t_token *)(token_list_aux->content);
		if (!token_list_aux)
			return (error_list(token_list));
		if (token->type == 0 || token->type == 2 || token->type == 3 || token->type == 9 || token->type == 17)
		{
			if (quote_list(token_list, i) == NULL)
				return (error_list(token_list));
			token->finished = 1;
		}
		i++;
	}
	return (token_list);
}
