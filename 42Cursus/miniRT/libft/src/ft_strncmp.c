/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:26:36 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 21:34:53 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to compare two strings up to a specified number of characters.
// PARAMETERS:
// - const char *s1: The first string to compare.
// - const char *s2: The second string to compare.
// - size_t n: The maximum number of characters to compare.
// DESCRIPTION:
// - This function compares the first n characters of the strings s1 and s2.
//   If they are equal up to the specified length, it returns 0.
//   If they differ, it returns the difference between the first two differing
//   characters (cast to unsigned char).
// OUTPUT:
// - Returns 0 if the strings are equal, a positive value if s1 > s2, or a
//   negative value if s1 < s2.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((i < n - 1) && s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>
#include <string.h>
int main() {
    const char *str1 = "Hello";
    const char *str2 = "HelLo";
    size_t n = 4;

    int result = ft_strncmp(str1, str2, n);
    printf("ft_strncmp: %d\n", result); // Expected: 0 (same up to 4 characters)

    return 0;
}
*/
