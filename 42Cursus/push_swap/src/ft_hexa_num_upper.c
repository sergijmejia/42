/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_num_upper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:24:38 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/02 11:44:20 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_hexa_num_upper(char *s, va_list args)
{
	char	*str;

	str = ft_hexa_num_lower(s, args);
	if (!str)
		return (NULL);
	ft_strtoupper(str);
	return (str);
}
