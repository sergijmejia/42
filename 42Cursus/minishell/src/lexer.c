/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:49 by smejia-a          #+#    #+#             */
/*   Updated: 2025/06/08 17:42:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Validacion de comillas simples. En caso de fallo retorna null*/
static char	*simple_quote_checker(char *str)
{
	str++;
	while (*str)
	{
		if (*str == '\'')
			return (str + 1);
		str++;
	}
	return (NULL);
}

/*Validacion de comillas dobles. En caso de fallo retorna NULL*/
static char	*double_quote_checker(char *str)
{
	str++;
	while (*str)
	{
		if (*str == '\"')
			return (str + 1);
		str++; 
	}
	return (NULL);
}

/*Numero de comandos separados
static int	number_commands(char **str)
{
	while (**str != ' '
}*/

/*Validacion de texto*/
static int	quote_checker(char *str)
{
	int	size;

	size = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			if (simple_quote_checker(str) == NULL)
				return (-1);
			size++;
		}
		else if (*str == '\"')
		{
			if (double_quote_checker(str) == NULL)
				return (-1);
			size++;
		}
		else
			//size = size + number_commands(&str);
			size++;
	}
	return (size);
}

/*Divide un string str en tokens*/
static **divide_by_char(char *str)
{
	char	**
	int	i;

	i = 0;
	while (str[i])
	{
		
	}
}

/*Almacena en un token la siguiente palabra*/
Token *ft_nextword (char **str)
{
	char	*new_word;
	t_token	tkn_lt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isanum(str[0][i]))
		i++;
	new_word = (char *) malloc (sizeof(char) * (i + 1));
	if (!new_word)
		return (NULL);
	new_word[i] = '\0';
	while (j < i)
	{
		new_word[j] = **str;
		*str++;
		j++;
	}
	tkn_lt.type = 1;
	tkn_lt->value = new_wprd;
	return (&tkn_lt);
}

/*Crea lexer. Pasa todos los argumentos de los string a una lista*/
t_list	*lexer(char *str)
{
	t_token	*token;

	token = NULL;
	while (*str)
	{
		if (ft_isalnum(*str))
			ft_lstadd_back(&token, ft_nextword (&str));
		else if (*str == "\'")
			ft_lstadd_back(&token, ft_singlequote(&str));
		else if (*str == '\"')
			ft_lstadd_back(&token, ft_doublequote(&str));
		else if (*str == '|')
			ft_lstadd_back(&token, ft_pipe(&str));
		else if (*str == '>')
			ft_lstadd_back(&token, ft_greaterthan(&str));
		else if (*str == '<')
			ft_lstadd_back(&token, ft_lessthan(&str));
		str++;
	}
	return (token);
}

/*
Dividir el input considerando las comillas. (Hecho - Falta errores)

Separar por espacios si no están dentro de comillas.

Detectar tokens especiales (|, >, >>, etc.).

Aplicar expansión de variables según las reglas de comillas.*/


/*
Tokens especiales a considerar:

Operadores de redirección y pipes

> : redirección de salida

>> : redirección de salida en modo append

< : redirección de entrada

<< : heredoc

| : pipe


Comillas

' : comillas simples → todo es literal, sin expansión.

" : comillas dobles → permiten expansión de variables, pero preservan espacios y caracteres especiales.



Expansión

$ : seguido de un nombre de variable ($PATH, $HOME, $?, etc.)

Dentro de ' no se expande

Dentro de " sí se expande


Espacios y tabulaciones

Sirven como separadores de argumentos (salvo dentro de comillas).

Hay que ignorar múltiples espacios consecutivos si no están entre comillas.


Backslash

\ : carácter de escape

Se usa para anular el significado especial del siguiente carácter.

Su uso puede depender del contexto (dentro de comillas simples no hace nada).

*/
