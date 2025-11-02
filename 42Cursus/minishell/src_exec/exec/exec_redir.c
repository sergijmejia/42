/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:55:17 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/02 12:05:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "exec.h"
#include "exec_heredoc.h"
#include "minishell_exec.h"
#include "env.h"

/* Abrir archivo según tipo de redirección */
static int	open_redir_file(char *filename, int type)
{
	int	flags;

	if (!filename)
		return (-1);
	if (type == TOKEN_P_GT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (type == TOKEN_P_DOUBLE_GT)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (type == TOKEN_P_LT)
		flags = O_RDONLY;
	else
		return (-1);
	return (open(filename, flags, 0644));
}

/* Buscar nombre de archivo en un nodo AST */
static char	*get_redir_filename_from_node(t_ast *node)
{
	char	*name;

	if (!node)
		return (NULL);
	if (node->value && node->value[0] && node->value[0][0] != '\0')
		return (node->value[0]);
	if (node->left_ast)
	{
		name = get_redir_filename_from_node(node->left_ast);
		if (name)
			return (name);
	}
	if (node->right_ast)
	{
		name = get_redir_filename_from_node(node->right_ast);
		if (name)
			return (name);
	}
	return (NULL);
}

/* Aplicar redirección a fd actual */
static void	apply_redirection(int fd, int type)
{
	if (type == TOKEN_P_GT || type == TOKEN_P_DOUBLE_GT)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			_exit(1);
	}
	else if (type == TOKEN_P_LT)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			_exit(1);
	}
}

/* Ejecuta comando con fd redirigidos */
static void	exec_redir_child(int fd_in, int fd_out, t_ast *node, t_exec_ctx *ctx)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		if (fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != -1)
		{
			apply_redirection(fd_out, node->type);
			close(fd_out);
		}
		exec_ast(node->left_ast, ctx->temp_vars, ctx->envp, ctx->parser_tmp_var);
		_exit(g_exit_status);
	}

	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 130;
}

/* Función principal exec_redir */
void	exec_redir(t_ast *node, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_var)
{
	int			fd_in = -1;
	int			fd_out = -1;
	char		*filename = NULL;
	t_exec_ctx	ctx;

	if (!node || !node->left_ast)
	{
		g_exit_status = 1;
		return ;
	}

	ctx.temp_vars = temp_vars;
	ctx.envp = envp;
	ctx.parser_tmp_var = parser_tmp_var;

	/* Heredoc */
	if (node->type == TOKEN_P_DOUBLE_LT)
	{
		// Si es standalone, ejecuta directamente
		if (!node->right_ast || !node->right_ast->left_ast)
		{
			exec_heredoc(node, temp_vars, envp, parser_tmp_var);
			return ;
		}
		// Caso heredoc dentro de otra redirección o pipe
		else {
			fd_in = exec_heredoc_prepare(node->right_ast);
			if (fd_in == -1)
				return ((void)(g_exit_status = 1));
			filename = get_redir_filename_from_node(node->right_ast->left_ast);
		}
	}
	else
		filename = get_redir_filename_from_node(node->right_ast);

	if (!filename && fd_in == -1)
	{
		g_exit_status = 1;
		return ;
	}

	/* Abrir archivo según tipo de redirección */
	if (node->type == TOKEN_P_GT || node->type == TOKEN_P_DOUBLE_GT
		|| node->type == TOKEN_P_LT)
	{
		if (node->type == TOKEN_P_GT || node->type == TOKEN_P_DOUBLE_GT)
    		fd_out = open_redir_file(get_redir_filename_from_node(node->left_ast), node->type);
		if (fd_out == -1)
		{
			perror(filename);
			g_exit_status = 1;
			if (fd_in != -1)
				close(fd_in);
			return ;
		}
	}

	exec_redir_child(fd_in, fd_out, node, &ctx);
}
