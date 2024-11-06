/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:20:55 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/02 13:27:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*zeromem;

	zeromem = (void *) malloc (nmemb * size);
	if (zeromem == NULL)
		return (NULL);
	ft_bzero(zeromem, (nmemb * size));
	return (zeromem);
}
