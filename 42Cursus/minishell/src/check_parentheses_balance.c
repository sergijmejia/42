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

/*Funcion que crea el archivo temporal y almacena la informacion introducida
static int	create_parentheses_file(char *line)
{
	int		fd;
	char	*str;
	size_t	len;

	fd = open(".tmp_parentheses", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	ft_printf("parentheses> ");
	str = get_next_line(0);
	len = ft_strlen(str);
	while (ft_strncmp(str, line, len - 1))
	{
		ft_putstr_fd(str, fd);
		free(str);
		ft_printf("parentheses> ");
		str = get_next_line(0);
		len = ft_strlen(str);
	}
	free(str);
	close(fd);
	return (0);
}*/

/*Funcion que agrega la informacion de fd a line y a heredoc_str
static char	**add_parentheses(int fd, char **line, char *heredoc)
{
	char	*aux;
	char	**parentheses_str;

	heredoc_str = heredoc_size(&fd);
	if (heredoc_str == NULL)
		return (NULL);
	if (fill_heredoc_str(heredoc_str, line, fd) == NULL)
	{
		close(fd);
		return (NULL);
	}
	aux = ft_strjoin(*line, heredoc);
	if (aux == NULL)
	{
		close(fd);
		free_str(parentheses_str);
		return (NULL);
	}
	free(*line);
	*line = aux;
	close(fd);
	return (parentheses_str);
}*/

/*Funcion que gestiona el correcto balance de parentesis
int	parentheses_balance(char **line)
{
	char		**parentheses_str;
	int			fd;

	if (check_parentheses_balance(*line) == 0)
		return (0);
	if (create_parentheses_file(*line))
	{
		free(*line);
		return (1);
	}
	fd = open(".tmp_parentheses", O_RDONLY);
	if (fd == -1)
	{
		unlink(".tmp_parentheses");
		free(*line);
		return (1);
	}
	parentheses_str = add_parentheses(fd, line);
	free(*line);
	unlink(".tmp_parentheses");
	if (parentheses_str == NULL)
		return (1);
	*line = *parentheses_str;
	return (parentheses_balance(line));
}*/