/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:57:27 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/04 17:58:10 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell_exec.h"

// env_export.c
int		export_assignment(char *assignment, char ***envp);

// env.c
int		builtin_env(char **envp);
int		unset_assignment(const char *name, char ***envp);

// env_build.c
char	**build_envp(t_temp_lst_exec *temp_vars, char **envp);

// env_temp_utils.c
void	free_temp_vars(t_temp_lst_exec **temp_vars);
void	add_temp_var(t_temp_lst_exec **temp_vars, char *name, char *value);
void	add_parser_tmp_var(t_list **parser_tmp_var,
			const char *name, const char *value);

// env_envp_utils.c
void	*free_partial_env(char **env, int filled);
void	free_envp(char **envp);
char	**clone_envp(char **envp);
char	*get_env_val(char **envp, const char *name);

// env_envp_update.c
int		update_env_var(char ***envp, const char *name, const char *value);

#endif
