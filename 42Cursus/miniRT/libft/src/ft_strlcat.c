/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:08:21 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 17:34:38 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to concatenate a string onto the end of another string.
// PARAMETERS:
// - char *dest: The destination string to which src will be appended.
// - const char *src: The source string to append.
// - size_t size: The size of the destination buffer.
// DESCRIPTION:
// - This function appends the source string to the destination string while
//   ensuring not to overflow the destination buffer.
// OUTPUT:
// - Returns the total length of the string it tried to create.
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = 0;
	src_len = 0;
	while (dest_len < size && dest[dest_len])
		dest_len++;
	while (src[src_len])
		src_len++;
	if (dest_len >= size)
		return (src_len + size);
	while ((dest_len + i < size - 1) && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
/*
#include <stdio.h>
#include "libft.h"
int main() {
    char dest[20] = "Hello, ";
    const char *src = "World!";
    size_t size = sizeof(dest);

    size_t total_length = ft_strlcat(dest, src, size);
    printf("Concatenated string: %s\n", dest);
    printf("Total length: %zu\n", total_length);

    return 0;
}
*/
