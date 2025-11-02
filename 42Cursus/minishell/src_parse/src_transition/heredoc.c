/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:41:44 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/22 12:51:36 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crea el archivo temporal y almacena la informacion introducida
mediante heredoc*/
static int	create_heredoc_file(char *here_doc)
{
	int		fd;
	char	*str;
	int		len;
	int		len_here_doc;

	fd = open(".tmp_minishell", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	ft_printf("> ");
	str = get_next_line(0);
	len = (int) ft_strlen(str);
	len_here_doc = (int)ft_strlen(here_doc);
	while (((len - 1) != len_here_doc) || (ft_strncmp(str, here_doc, len - 1)))
	{
		ft_putstr_fd(str, fd);
		free(str);
		ft_printf("> ");
		str = get_next_line(0);
		len = (int) ft_strlen(str);
	}
	free(str);
	if (close(fd) == -1)
		return (1);
	return (0);
}

/*Funcio que ingresa, linea por linea, los strings en el archivo temporal*/
static char	**fill_heredoc_str(char **heredoc_str, char **line, int fd)
{
	int		i;
	char	*str;
	char	*aux;

	str = get_next_line(fd);
	i = 0;
	while (str != NULL)
	{
		aux = ft_strjoin(*line, str);
		heredoc_str[i] = ft_strdup(str);
		heredoc_str[i + 1] = NULL;
		free(str);
		if (aux == NULL || heredoc_str[i] == NULL)
		{
			free(aux);
			free_str(heredoc_str);
			return (NULL);
		}
		free(*line);
		*line = aux;
		str = get_next_line(fd);
		i++;
	}
	heredoc_str[i] = NULL;
	return (heredoc_str);
}

/*Funcion que agrega la informacion de fd a line y a heredoc_str*/
static char	**add_heredoc(int fd, char **line, char *heredoc)
{
	char	*aux;
	char	**heredoc_str;

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
		return (free_str(heredoc_str));
	}
	free(*line);
	*line = ft_strjoin(aux, "\n");
	free(aux);
	close(fd);
	if (*line == NULL)
		return (free_str(heredoc_str));
	return (heredoc_str);
}

/*Funcion que crea y abre el archivo temporal*/
static int	create_open_heredoc(char *heredoc)
{
	int	fd;

	if (create_heredoc_file(heredoc))
	{
		free(heredoc);
		return (-1);
	}
	fd = open(".tmp_minishell", O_RDONLY);
	if (fd == -1)
	{
		unlink(".tmp_minishell");
		free(heredoc);
		return (-1);
	}
	return (fd);
}

/*Funcion que gestiona el heredoc*/
int	heredoc(t_aux *aux, int pos, char **line)
{
	t_token_ast	*token_tr;
	char		*heredoc;
	char		**heredoc_str;
	int			fd;
	t_list		**token_list;

	token_list = aux->token_list;
	token_tr = (t_token_ast *)((ft_lstpos(*token_list, pos))->content);
	heredoc = ft_strdup((token_tr->value)[0]);
	if (heredoc == NULL)
		return (1);
	fd = create_open_heredoc(heredoc);
	if (fd == -1)
		return (1);
	heredoc_str = add_heredoc(fd, line, heredoc);
	free(heredoc);
	unlink(".tmp_minishell");
	if (heredoc_str == NULL)
		return (1);
	if (heredoc_var_expansion(heredoc_str, aux, pos) == NULL)
		return (1);
	free_str(token_tr->value);
	token_tr->value = heredoc_str;
	return (0);
}
