/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:33:24 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/09 10:46:21 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_strtoupper(void *str)
{
	char	*aux;

	if (str == NULL)
		return ;
	aux = (char *)str;
	while (*aux)
	{
		*aux = ft_toupper(*aux);
		aux++;
	}
}
