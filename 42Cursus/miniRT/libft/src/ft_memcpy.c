/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:46:41 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 21:27:43 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to copy a block of memory from source to destination.
// PARAMETERS:
// - void *dest: Pointer to the destination memory area.
// - const void *src: Pointer to the source memory area.
// - size_t n: The number of bytes to copy.
// DESCRIPTION:
// - This function copies n bytes from the memory area pointed to by src
//   to the memory area pointed to by dest. If dest and src overlap,
//   behavior is undefined.
// OUTPUT:
// - Returns a pointer to the destination memory area.
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
    char src[] = "Hello, World!";
    char dest[20];

    ft_memcpy(dest, src, sizeof(src));
    printf("Destination after memcpy: %s\n", dest);

    return 0;
}
*/
