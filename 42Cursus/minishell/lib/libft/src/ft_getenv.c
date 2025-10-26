/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:22:14 by smejia-a          #+#    #+#             */
/*   Updated: 2025/10/20 15:04:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Funcion que busca en env la variable name*/
char	*ft_getenv(char **env, const char *name)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	while (env[i] != NULL)
	{
		len = (int) ft_strlen(name);
		if ((ft_strncmp(env[i], name, len) == 0) && env[i][len] == '=')
			break ;
		i++;
	}
	if (env[i] == NULL)
	{
		str = (char *) malloc (sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = ft_strdup(&env[i][len + 1]);
	if (str == NULL)
		return (NULL);
	return (str);
}
