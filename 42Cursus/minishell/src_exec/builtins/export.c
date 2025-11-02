/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:40:56 by rafaguti          #+#    #+#             */
/*   Updated: 2025/10/28 02:53:52 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "export_utils.h"

/**
 * @brief Compare function for qsort using ft_strncmp.
 */
static int	strcmp_ptr(const void *a, const void *b)
{
	return (ft_strncmp(*(char **)a, *(char **)b, 4096));
}

/**
 * @brief Sorts all_vars and prints them in bash export format.
 *
 * Skips the special variable "_".
 *
 * @param all_vars Array of variables
 * @param count Number of variables
 */
void	print_sorted_vars(char **all_vars, int count)
{
	int		i;
	char	*eq;

	qsort(all_vars, count, sizeof(char *), strcmp_ptr);
	i = 0;
	while (i < count)
	{
		if (ft_strncmp(all_vars[i], "_=", 2) == 0)
		{
			free(all_vars[i]);
			i++;
			continue ;
		}
		eq = ft_strchr(all_vars[i], '=');
		if (eq)
			printf("declare -x %.*s=\"%s\"\n",
				(int)(eq - all_vars[i]), all_vars[i], eq + 1);
		else
			printf("declare -x %s\n", all_vars[i]);
		free(all_vars[i]);
		i++;
	}
	free(all_vars);
}

/**
 * @brief Print all exported variables in sorted order like bash,
 *        skipping the special variable "_".
 *
 * @param envp Environment array
 * @param temp_vars Temporary variable list
 */
static void	print_exported_vars(char **envp)
{
	int		count;
	char	**all_vars;

	count = count_vars(envp);
	all_vars = malloc(sizeof(char *) * (count + 1));
	if (!all_vars)
		return ;
	count = fill_all_vars(all_vars, envp);
	print_sorted_vars(all_vars, count);
}

/**
 * @brief Builtin export: add variables or print all if no args
 *
 * @param args Arguments array (args[0] = "export")
 * @param temp_vars Temporary variable list
 * @param envp Pointer to environment array
 * @return 0 on success, 1 on error
 */
int	builtin_export(char **args, t_temp_lst_exec **temp_vars,
		char ***envp, t_list **parser_tmp_vars)
{
	int	i;

	if (!args)
		return (1);
	if (!args[1])
	{
		print_exported_vars(*envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		add_var(temp_vars, args[i], envp, parser_tmp_vars);
		i++;
	}
	return (0);
}
