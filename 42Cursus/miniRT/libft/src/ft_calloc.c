/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:14:32 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/31 19:13:20 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

// Allocates memory for an array of nmemb elements of size bytes each
// PARAMETERS:
// - size_t nmemb: Number of elements to allocate
// - size_t size: Size of each element in bytes
// DESCRIPTION:
// - This function allocates memory for an array of nmemb elements, each of
//   size bytes. The total allocated memory is initialized to zero.
// - If nmemb or size is zero, malloc(0) is called, which may return NULL or
//   a unique pointer that can be safely passed to free.
// - If an overflow occurs during the multiplication of nmemb and size,
//   NULL is returned to indicate allocation failure.
// - If allocation fails, NULL is returned.
// OUTPUT:
// - Returns a pointer to the allocated memory, or NULL if the allocation fails.
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total_size = nmemb * size;
	if ((size != 0 && total_size / size != nmemb)
		|| (nmemb != 0 && total_size / nmemb != size))
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
/*
#include <stdio.h>
int main(void)
{
    int *arr;
    size_t n = 5;

    arr = ft_calloc(n, sizeof(int));
    if (arr)
    {
        printf("Test ft_calloc\n");
        for (size_t i = 0; i < n; i++)
            printf("arr[%zu] = %d\n", i, arr[i]);
        free(arr);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }
    return 0;
}
*/
