/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:23:45 by rafaguti          #+#    #+#             */
/*   Updated: 2024/09/16 23:22:26 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function to locate the first occurrence of a character in a string.
// PARAMETERS:
// - const char *s: The input string to be searched.
// - int c: The character to locate, passed as an integer.
// DESCRIPTION:
// - This function scans the string for the specified character and returns a
//   pointer to its first occurrence or NULL if not found.
// OUTPUT:
// - Returns a pointer to the first occurrence of the character or NULL.
char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p != '\0' && (*p != (char)c))
		p++;
	if (*p == (char)c)
		return (p);
	return (0);
}
/*
#include <stdio.h>
#include "libft.h"

int main() {
    const char *s = "Hello, World!";
    int c = 'o';

    char *result = ft_strchr(s, c);
    if (result) {
        printf("Found '%c' at position: %ld\n", c, result - s);
    } else {
        printf("Character '%c' not found in string.\n", c);
    }

    return 0;
}
*/
