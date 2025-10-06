/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:41:44 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/05 14:41:46 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que crea el archivo temporal y almacena la informacion introducida
mediante heredoc*/
static int	create_heredoc_file(char *here_doc)
{
	int		fd;
	char	*str;
	size_t	len;

	fd = open(".tmp_minishell", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	ft_printf("> ");
	str = get_next_line(0);
	len = ft_strlen(str);
	while (ft_strncmp(str, here_doc, len - 1))
	{
		ft_putstr_fd(str, fd);
		free(str);
		ft_printf("> ");
		str = get_next_line(0);
		len = ft_strlen(str);
	}
	free(str);
	close(fd);
	return (0);
}

static int	heredoc_size(int fd)
{
	char	*str;
	int		size;

	size = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		size++;
		free(str);
		str = get_next_line(fd);
	}
	return (size);
}

/*Funcion que agrega la informacion de fd a line y a heredoc_str*/
static char	**add_heredoc(int fd, char **line, char *heredoc)
{
	int		i;
	int		size;
	char	*aux;
	char	*str;
	char	**heredoc_str;

	size = heredoc_size(fd);
	close(fd);
	fd = open(".tmp_minishell", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (size == -1)
		return (NULL);
	heredoc_str = (char **) malloc ((size + 2) * sizeof(char *));
	if (heredoc_str == NULL)
	{
		close(fd);
		return (NULL);
	}
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
	aux = ft_strjoin(*line, heredoc); //<----falta agregar el ultimo elemento a line (EOF) para el historial
	heredoc_str[size + 1] = NULL;
	return (heredoc_str);
}

/*Funcion que gestiona el heredoc*/
int	heredoc(t_list **token_list, int pos, char **line)
{
	t_token_ast	*token_tr;
	char		*heredoc;
	char		**heredoc_str;
	int			fd;

	token_tr = (t_token_ast *) ((ft_lstpos(*token_list, pos))->content);
	heredoc = ft_strdup((token_tr->value)[0]);
	if (heredoc == NULL)
		return (1);
	if (create_heredoc_file(heredoc))
	{
		free(heredoc);
		return (1);
	}
	fd = open(".tmp_minishell", O_RDONLY);
	if (fd == -1)
	{
		unlink(".tmp_minishell");
		free(heredoc);
		return (1);
	}
	heredoc_str = add_heredoc(fd, line, heredoc);
	close(fd);
	free(heredoc);
	unlink(".tmp_minishell");
	if (heredoc_str == NULL)
		return (1);
	free_str(token_tr->value);
	tolen_tr->value = heredoc_str;
	return (0);
}
