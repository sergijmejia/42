/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_newline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:40:37 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/01 16:41:15 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_newline(char *str)
{
	int		i;
	char	c;

	if (!str)
		return (-1);
	i = 0;
	while (str && str[i] != '\0')
	{
		c = str[i];
		if (c == '\n')
			return (i);
		i++;
	}
	return (-1);
}
