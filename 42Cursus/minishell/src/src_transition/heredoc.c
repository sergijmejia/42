/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:41:44 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 16:25:21 by smejia-a         ###   ########.fr       */
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
	close(fd);
	return (0);
}

/*Funcion que crea el heredoc_str*/
static char	**heredoc_size(int *fd)
{
	char	*str;
	int		size;
	char	**heredoc_str;

	size = 0;
	str = get_next_line(*fd);
	while (str != NULL)
	{
		size++;
		free(str);
		str = get_next_line(*fd);
	}
	close(*fd);
	*fd = open(".tmp_minishell", O_RDONLY);
	if (*fd == -1)
		return (NULL);
	heredoc_str = (char **) malloc ((size + 2) * sizeof(char *));
	if (heredoc_str == NULL)
	{
		close(*fd);
		return (NULL);
	}
	return (heredoc_str);
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
		free_str(heredoc_str);
		return (NULL);
	}
	free(*line);
	*line = aux;
	close(fd);
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

/*Funcion que encuentra la siguiente comilla*/
static int	next_quote(char *str, int pos)
{
	char	c;

	c = str[pos];
	pos++;
	while (str[pos] && str[pos] != c)
		pos++;
	return (pos);
}

/*Funcion que devueve el comando*/
static char	*get_command(char *str, int x)
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

/*Funcion que remplaza el la $VAR en posicion i por el new_str*/
static int	replace_string(char **str, char *new_str, int command_len, int pos)
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
	write(1, replace_str, len);
	write(1, "\n", 1);
	free(*str);
	*str = replace_str;
	return (pos + new_len);
}

/*Funcion que expande las variables en una str*/
static char	*simple_var_expansion(char *str, char **env, t_list **tmp_var)
{
	char	*new_str;
	char	*command;
	int		command_len;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i = next_quote(str, i);
			i++;
		}
		else if ((str)[i] == '$' && (str)[i + 1] != '\0')
		{
			if ((str)[i + 1] != '$')
			{
				if (str[i + 1] == '?')
				{
					command_len = 2;
					new_str = ft_itoa(g_exit_status);
				}
				else
				{
					command = get_command(str, i);
					if (command == NULL)
						return (NULL);
					command_len = ft_strlen(command);
					new_str = find_var((&command[1]), tmp_var);
					if (new_str == NULL)
					{
						free(command);
						return (NULL);
					}
					if (new_str[0] == '\0')
					{
						free(new_str);
						new_str = ft_getenv(env, &command[1]);
					}
					free(command);
				}
				if (new_str == NULL)
					return (NULL);
				i = replace_string(&str, new_str, command_len, i);
				free(new_str);
				if (i == -1)
				{
					free(new_str);
					return (NULL);
				}
			}
			else
				i++;
		}
		else
			i++;
	}
	return (str);
}

/*Funcion que expande variables en heredoc*/
static char	**heredoc_var_expansion(char **str, t_aux *aux)
{
	int		i;
	char	**env;
	t_list	**tmp_var;

	env = aux->env;
	tmp_var = aux->tmp_var;
	i = 0;
	while (str[i])
	{
		str[i] = simple_var_expansion(str[i], env, tmp_var);
		if (str[i] == NULL)
			return (free_str(str));
		i++;
	}
	return (str);
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
	if (heredoc_var_expansion(heredoc_str, aux) == NULL)
		return (1);
	free_str(token_tr->value);
	token_tr->value = heredoc_str;
	return (0);
}
