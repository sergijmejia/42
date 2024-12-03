/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:43:57 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/26 15:44:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
/*#include <string.h>
#include <stdio.h>*/

void	ft_bzero(void *ptr, size_t num)
{
	ptr = ft_memset(ptr, 0, num);
}
/*
int	main(int argc, char *argv[])
{
	char	*new_str;
	char	*new_strft;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	new_strft = argv[1];
	ft_bzero(new_strft, ft_strlen(new_strft));
	new_str = argv[1];
	bzero(new_str, ft_strlen(new_str));
	printf("El nuevo string con la funcion ft_bzero es %s\n", new_strft);
	printf("El nuevo string con la cuncion bzero es %s\n", new_str);
	return (0);
}
*/
