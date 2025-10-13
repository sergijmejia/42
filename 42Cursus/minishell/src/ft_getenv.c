/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:22:14 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/07 15:05:39 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que busca en env la variable name*/
char	*ft_getenv(char **env, const char *name)
{
	int		i;
	int		len_name;
	char	*str;

	i = 0;
	while (env[i] != NULL)
	{
		len_name = (int) ft_strlen(name);
		if (ft_strncmp(env[i], name, len_name) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	str = ft_strdup(&env[i][len_name + 1]);
	if (str == NULL)
		return (NULL);
	return (str);
}
