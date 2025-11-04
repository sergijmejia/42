/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:58:41 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 17:58:58 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_COMMAND_UTILS_H
# define EXEC_COMMAND_UTILS_H

# include "minishell_exec.h"

void	fork_and_exec(t_ast *node, char **env_for_exec);
int		check_export_args(const char *arg);

#endif
