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

#include "libft.h"
//#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*zeromem;

	zeromem = (void *) malloc (nmemb * size);
	if (zeromem == NULL)
		return (NULL);
	ft_bzero(zeromem, (nmemb * size));
	return (zeromem);
}
/*
int	main(int argc, char *argv[])
{
	int		num;
	int		i;
	char	*char_memft;
	char	*char_mem;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	printf("antes del atoi\n");
	num = ft_atoi(argv[1]);
	printf("despues del atoi el valor de num es: %d\n", (int) num);
	char_memft = ft_calloc((size_t) num, sizeof(char));
	char_mem = calloc((size_t) num, sizeof(char));
	if ((char_mem == NULL) || (char_memft == NULL))
	{
		printf("Error al asignar memoria");
		return (1);
	}
	printf("la memoria con ft_calloc es:");
	i = 0;
	while (i < num)
	{
		printf(" %c", char_memft[i]);
		i++;
	}
	printf("\n");
	printf("la memoria con calloc es:");
        i = 0;
        while (i < num)
        {
                printf(" %c", char_mem[i]);
                i++;
        }
        printf("\n");
	free(char_memft);
	free(char_mem)
	return (0);
}
*/
