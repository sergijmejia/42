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
	while (ft_strncmp(str, here_doc, len - 1) || str[0] == '\n')
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

int	heredoc(t_list **token_list, int pos, char **line)
{
	t_token_ast	*token_tr;
	char		*str;
	char		*aux;
	char		*here_doc;
	int			fd;

	token_tr = (t_token_ast *) ((ft_lstpos(*token_list, pos))->content);
	here_doc = (token_tr->value)[0];
	if (create_heredoc_file(here_doc))
		return (1);
	fd = open(".tmp_minishell", O_RDONLY);
	if (fd == -1)
	{
		unlink(".tmp_minishell");
		return (1);
	}
	str = get_next_line(fd);
	while (str != NULL)
	{
		aux = ft_strjoin(*line, str);
		free(str);
		if (aux == NULL)
			return (1);
		free(*line);
		*line = aux;
		str = get_next_line(fd);
	}
	unlink(".tmp_minishell");
	return (0);
}
