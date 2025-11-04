/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:03:30 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 18:03:48 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PATH_H
# define EXEC_PATH_H

char	*get_path_from_env(char **envp);
char	*join_path(const char *dir, const char *cmd);

#endif
