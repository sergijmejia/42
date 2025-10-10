/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:16:22 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/10 15:03:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica que un enviroment contiene PWD, SHLVL, _*/
static int	check_env(char **envp)
{
	int		missing;
	int		i;

	missing = 3;
	if (envp == NULL)
		return (3);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			missing--;
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			missing--;
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			missing--;
		if (missing == 0)
			return (0);
		i++;
	}
	return (missing);
}

/*Funcion que pasa los datos de cualquier linea de envp a env exepto PWD, _*/
static char	*copy_envp_line(char **envp, int pos_envp, int *check)
{
	char	*env;
	int		len_lvl;
	int		pos_lvl;

	if (ft_strncmp(envp[pos_envp], "SHLVL=", 6) == 0)
	{
		len_lvl = (int) ft_strlen(envp[pos_envp]);
		pos_lvl = 6;
		while (pos_lvl < len_lvl)
		{
			if (!ft_isdigit(envp[pos_envp][pos_lvl]))
			{
				env = ft_strdup("SHLVL=1");
				break ;
			}
			pos_lvl++;
		}
		if (pos_lvl == len_lvl)
			env = ft_strdup(envp[pos_envp]);
		*check = 1;
	}
	else
		env = ft_strdup(envp[pos_envp]);
	return (env);
}

/*Funcion que crea env a partir de envp sin PWD, _*/
static char	**create_env(char **envp, char **env, int *pos_env, int *check)
{
	int	pos_envp;
	int	len_envp;

	*pos_env = 0;
	pos_envp = 0;
	*check = 0;
	len_envp = doublestr_len(envp);
	while (pos_envp < len_envp)
	{
		if (ft_strncmp(envp[pos_envp], "PWD=", 4) == 0)
			pos_envp++;
		else if (ft_strncmp(envp[pos_envp], "_=", 2) == 0)
			pos_envp++;
		else 
		{
			env[*pos_env] = copy_envp_line(envp, pos_envp, check);
			if (env[*pos_env] == NULL)
				return (free_str(env));
			(*pos_env)++;
			pos_envp++;
		}
	}
	env[*pos_env] = NULL;
	return (env);
}

/*Funcion que agrega las lineas PWD y _ al env*/
static char	**add_pwd_(char **env, int pos_env, int check)
{
	char	*aux;

	aux = getcwd(NULL, 0);
	if (aux == NULL)
		return (free_str(env));
	env[pos_env] = ft_strjoin("PWD=", aux);
	free(aux);
	if (env[pos_env] == NULL)
		return (free_str(env));
	pos_env++;
	env[pos_env] = ft_strdup("_=]");
	if (env[pos_env] == NULL)
		return (free_str(env));
	pos_env++;
	if (check == 0)
	{
		env[pos_env] = ft_strdup("SHLVL=1");
		if (env[pos_env] == NULL)
			return (free_str(env));
		pos_env++;
	}
	env[pos_env] = NULL;
	return (env);
}

/*Funcion que crea o modifica un env si no recibimos la informacion minima*/
char	**dup_env(char **envp)
{
	char	**env;
	int		missing;
	int		len_envp;
	int		pos_env;
	int		check;

	missing = check_env(envp);
	len_envp = doublestr_len(envp);
	env = (char **) malloc ((len_envp + missing + 1) * sizeof (char *));
	if (env == NULL)
		return (NULL);
	check = 0;
	if (create_env(envp, env, &pos_env, &check) == NULL)
		return (NULL);
	if (add_pwd_(env, pos_env, check) == NULL)
		return(NULL);
	return (env);
}
