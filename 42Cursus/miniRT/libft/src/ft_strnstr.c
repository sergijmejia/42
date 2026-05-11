/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:05:11 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 20:25:41 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to locate a substring in a string up to a specified length.
// PARAMETERS:
// - const char *s: The string to be searched.
// - const char *sub: The substring to find.
// - size_t len: The maximum number of characters to search within.
// DESCRIPTION:
// - This function searches for the first occurrence of the substring 'sub'
//   in the string 's', stopping after 'len' characters. If the substring
//   is found, a pointer to the beginning of the substring in 's' is returned.
// OUTPUT:
// - Returns a pointer to the located substring, or NULL if not found.
char	*ft_strnstr(const char *s, const char *sub, size_t len)
{
	size_t	pos;
	size_t	i;

	if (!*sub)
		return ((char *)s);
	pos = 0;
	while (s[pos] != '\0' && pos < len)
	{
		if (s[pos] == sub[0])
		{
			i = 0;
			while (sub[i] != '\0' && s[pos + i] == sub[i] && (pos + i) < len)
				i++;
			if (sub[i] == '\0')
				return ((char *)&s[pos]);
		}
		pos++;
	}
	return ((void *)0);
}
/*
#include <stdio.h>
#include <string.h>
int main() {
    const char *haystack = "This is a simple string";
    const char *needle = "simple";
    size_t len = 20;

    char *result = ft_strnstr(haystack, needle, len);
    if (result) {
        printf("ft_strnstr: Found substring at position: %ld\n",
				result - haystack);
    } else {
        printf("ft_strnstr: Substring not found\n");
    }

    return 0;
}
*/
