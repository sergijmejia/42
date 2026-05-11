/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:46:14 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 17:21:10 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to fill a block of memory with a specified byte.
// PARAMETERS:
// - void *s: Pointer to the memory area to fill.
// - int c: The byte value to set (interpreted as unsigned char).
// - size_t n: The number of bytes to fill.
// DESCRIPTION:
// - This function sets the first n bytes of the memory area pointed to by s
//   to the specified value c. The value is passed as an int, but the
//   function fills memory with the low-order byte of this value.
// OUTPUT:
// - Returns a pointer to the memory area s.
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	value;

	p = (unsigned char *)s;
	value = (unsigned char )c;
	while (n--)
	{
		*p = value;
		p++;
	}
	return (s);
}
/*
#include <stdio.h>
int main(void)
{
    char str[20] = "Hello, World!";
    printf("Before memset: %s\n", str);

    ft_memset(str, '*', 5); // Fill first 5 bytes with '*'
    printf("After memset: %s\n", str); // Expected: "***** World!"

    return 0;
}
*/
