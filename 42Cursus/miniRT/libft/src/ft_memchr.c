/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:28:51 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 22:07:48 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to locate the first occurrence of a byte in a block of memory.
// PARAMETERS:
// - const void *s: Pointer to the memory area to search.
// - int c: The byte to search for.
// - size_t n: The number of bytes to scan.
// DESCRIPTION:
// - This function scans the first n bytes of the memory area pointed to by s
//   for the first occurrence of the byte c. If found, it returns a pointer
//   to that location; otherwise, it returns NULL.
// OUTPUT:
// - Returns a pointer to the first occurrence of c, or NULL if not found.
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*byte_ptr;
	unsigned char		target_byte;

	byte_ptr = (const unsigned char *)s;
	target_byte = (unsigned char)c;
	while (n--)
	{
		if (*byte_ptr == target_byte)
			return ((void *)byte_ptr);
		byte_ptr++;
	}
	return ((void *)0);
}
/*
#include <stdio.h>
int main(void)
{
    char str[] = "Hello, World!";
    char *result;

    result = ft_memchr(str, 'o', sizeof(str));
    if (result)
        printf("Found 'o' at position: %ld\n", result - str);
    else
        printf("'o' not found.\n");

    result = ft_memchr(str, 'z', sizeof(str));
    if (result)
        printf("Found 'z' at position: %ld\n", result - str);
    else
        printf("'z' not found.\n");

    return 0;
}
*/
