/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:26:24 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/02 13:18:24 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen((char *) s);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	len = ft_strlcpy(str, s, len + 1);
	return (str);
}
