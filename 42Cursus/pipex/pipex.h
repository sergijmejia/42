/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:47:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/08 17:45:18 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <aio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

/*Estructura de los argumentos recbidos en el main*/
typedef struct s_arguments
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_arguments;

/*Funciones de manejo de errores*/

int		ft_print_file_error(char *file, int saved_errno);
int		ft_print_command_error(char *cmd);
void	print_error(char *str);
void	ft_print_error(void);

/*Utils*/
char	*ft_clean_split(char **str);
char	*build_cmd_path(char *cmd, char **paths);
char	*get_cmd_path(char *cmd, char **envp);
void	execve_error(char **cmd_args);
void	execute_command(char **cmd_args, char **envp);

/*Child_Parent*/
void	parent(int fd_file[2], int fd_pipe[2], t_arguments arg);
void	child(int fd, int pipe[2], int saved_errno, t_arguments arg);

/*Bonus Child_Parent*/
void	parent_multiple(int file[2], int pipe[2], t_arguments a, int sv_err);
void	first_child(int fd, int pipe[2], int saved_errno, t_arguments arg);

#endif
