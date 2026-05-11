/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:00:58 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 17:30:31 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to compare two blocks of memory byte by byte.
// PARAMETERS:
// - const void *s1: Pointer to the first memory block.
// - const void *s2: Pointer to the second memory block.
// - size_t n: The number of bytes to compare.
// DESCRIPTION:
// - This function compares the first n bytes of the memory areas pointed to
//   by s1 and s2. It returns an integer less than, equal to, or greater than
//   zero if the first n bytes of s1 is found to be less than, to match, or
//   be greater than the first n bytes of s2.
// OUTPUT:
// - Returns a negative integer if s1 is less than s2,
//   zero if they are equal, or a positive integer if s1 is greater than s2.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*byte_ptr1;
	unsigned char	*byte_ptr2;

	byte_ptr1 = (unsigned char *)s1;
	byte_ptr2 = (unsigned char *)s2;
	while (n--)
	{
		if (*byte_ptr1 != *byte_ptr2)
			return (*byte_ptr1 - *byte_ptr2);
		byte_ptr1++;
		byte_ptr2++;
	}
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";

    int result1 = ft_memcmp(str1, str2, sizeof(str1));
    int result2 = ft_memcmp(str1, str3, sizeof(str1));

    printf("Comparing str1 and str2: %d\n", result1); // Should be 0
    printf("Comparing str1 and str3: %d\n", result2); // Should be negative

    return 0;
}
*/
