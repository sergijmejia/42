/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:40:13 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/11 20:33:18 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countwords(const char *s, char c)
{
	int	i;
	int	split;
	int	word;

	if (s == NULL)
		return (0);
	i = 0;
	split = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c && split)
			split = 0;
		if (s[i] != c && !split)
		{
			word++;
			split = 1;
		}
		i++;
	}
	return (word);
}
