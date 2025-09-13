/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:25:11 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/10 17:14:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	int		i;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if ((dst == NULL) || (src == NULL))
		return (len_d + len_s);
	if (size <= len_d)
		return (size + len_s);
	i = 0;
	while (src[i] && ((len_d + i + 1) < size))
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}
/*
int	main(int argc, char *argv[])
{
	//char	*src;
	char	*src_ft;
	//char	*dst;
	char	*dst_ft;
	char	*src_null;
	size_t	len;
	//size_t	aux;
	size_t	aux_ft;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	len = 100;
	//dst = (char *) malloc (len * sizeof(char));
	//aux = ft_strlcpy(dst, argv[1], len);
	dst_ft = (char *) malloc (len * sizeof(char));
	src_null = NULL;
	//len = ft_strlen(dst_ft);
	aux_ft = ft_strlcpy(dst_ft, argv[1], sizeof(dst_ft));
	//src = "Segundo string con funcion strlcat";
	src_ft = "Segundo string con funcion ft_strlcat";
	//aux = strlcat(dst, src, sizeof(dst));
	//printf("El nuevo string con la funcion strlcat es %s\n", dst);
	aux_ft = ft_strlcat(dst_ft, src_null, len);
	printf("El nuevo string con la funcion ft_strlcat es %s\n", dst_ft);
	printf("la medida necesaria para el string es %d\n", (int) aux_ft);
	//free(dst);
	free(dst_ft);
	return (0);
}*/
