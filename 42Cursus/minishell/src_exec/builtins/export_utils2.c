/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:43:54 by rafaguti          #+#    #+#             */
/*   Updated: 2025/11/03 15:43:55 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "var_utils.h"
#include "export_utils.h"
#include "minishell_exec.h"
#include "env.h"
#include <stdlib.h>
#include <stdio.h>

static void	handle_no_equal(char *arg, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_vars)
{
	char	*tmp_val;

	tmp_val = get_temp_var_value(*temp_vars, arg);
	if (tmp_val)
	{
		if (is_valid_var_name(arg))
			update_env_var(envp, arg, tmp_val);
		remove_local_var(temp_vars, arg);
		remove_parser_tmp_var(parser_tmp_vars, arg);
		return ;
	}
	tmp_val = get_parser_tmp_var_value(*parser_tmp_vars, arg);
	if (tmp_val)
	{
		if (is_valid_var_name(arg))
			update_env_var(envp, arg, tmp_val);
		remove_parser_tmp_var(parser_tmp_vars, arg);
		return ;
	}
	if (!get_env_val(*envp, arg) && is_valid_var_name(arg))
		export_assignment(arg, envp);
}

static int	parse_name_value(char *arg, char **name, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	*name = ft_substr(arg, 0, eq - arg);
	if (!*name)
		return (0);
	*value = ft_strdup(eq + 1);
	if (!*value)
	{
		free(*name);
		return (0);
	}
	return (1);
}

static int	validate_and_update(char *name, char *value, char ***envp)
{
	if (!is_valid_var_name(name))
	{
		fprintf(stderr,
			"minishell: export: `%s': not a valid identifier\n", name);
		free(name);
		free(value);
		return (0);
	}
	if (get_env_val(*envp, name))
	{
		update_env_var(envp, name, value);
		free(name);
		free(value);
		return (0);
	}
	return (1);
}

static void	handle_equal(char *arg, t_temp_lst_exec **temp_vars,
		char ***envp)
{
	char	*name;
	char	*value;

	if (!parse_name_value(arg, &name, &value))
		return ;
	if (!validate_and_update(name, value, envp))
		return ;
	insert_temp_var(temp_vars, name, value);
	export_assignment(arg, envp);
}

void	add_var(t_temp_lst_exec **temp_vars, char *arg,
		char ***envp, t_list **parser_tmp_vars)
{
	if (!arg || !*arg)
		return ;
	if (!ft_strchr(arg, '='))
	{
		handle_no_equal(arg, temp_vars, envp, parser_tmp_vars);
		return ;
	}
	handle_equal(arg, temp_vars, envp);
}
