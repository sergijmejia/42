/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:04:43 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 22:07:32 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to safely move a block of memory from source to destination.
// PARAMETERS:
// - void *dest: Pointer to the destination memory area.
// - const void *src: Pointer to the source memory area.
// - size_t n: The number of bytes to move.
// DESCRIPTION:
// - This function copies n bytes from the memory area pointed to by src
//   to the memory area pointed to by dest. It handles overlapping regions
//   safely by determining the direction of the copy.
// OUTPUT:
// - Returns a pointer to the destination memory area.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s)
		return (dest);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
    char str[] = "Hello, World!";
    printf("Before memmove: %s\n", str);

    ft_memmove(str + 7, str, 6); // Move "Hello" into "World!"
    printf("After memmove: %s\n", str); // Expected: "Hello, Hello!"

    return 0;
}
*/
