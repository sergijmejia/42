/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:07:06 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 17:27:38 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to copy a string into another, ensuring null-termination.
// PARAMETERS:
// - char *dest: The destination buffer.
// - const char *src: The source string to copy.
// - size_t size: The size of the destination buffer.
// DESCRIPTION:
// - This function copies the string from src to dest, ensuring that it will
//   always null-terminate the destination buffer if size is greater than 0.
// OUTPUT:
// - Returns the total length of the source string.
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	if (size > 0)
	{
		while (src[src_len] && (src_len < size - 1))
		{
			dest[src_len] = src[src_len];
			src_len++;
		}
		dest[src_len] = '\0';
	}
	while (src[src_len])
		src_len++;
	return (src_len);
}
/*
#include <stdio.h>
#include "libft.h"
int main() {
    char dest[20];
    const char *src = "Hello, World!";
    size_t size = sizeof(dest);

    size_t copied_length = ft_strlcpy(dest, src, size);
    printf("Copied string: %s\n", dest);
    printf("Length of source string: %zu\n", copied_length);

    return 0;
}
*/
