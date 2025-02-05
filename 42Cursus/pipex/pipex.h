/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:47:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/05 12:36:14 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <aio.h>
# include <sys/wait.h>
#include <errno.h>
#include <string.h>

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


#endif


