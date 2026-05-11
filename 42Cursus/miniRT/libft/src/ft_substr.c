/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:44:24 by rafaguti          #+#    #+#             */
/*   Updated: 2024/09/21 01:47:41 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

// Function to create a substring from a given string.
// PARAMETERS:
// - char const *s: The string from which to create a substring.
// - unsigned int start: The starting index of the substring.
// - size_t len: The maximum length of the substring.
// DESCRIPTION:
// - This function allocates memory for a substring from 's', starting at
//   'start' for 'len' characters. If 'start' is beyond the end of the string,
//   an empty string is returned. If memory allocation fails, NULL is returned.
// OUTPUT:
// - Returns a pointer to the newly created substring, or NULL on failure.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
/*
#include <stdio.h>
#include <string.h>
int main() {
    const char *str = "Hello World!";
    unsigned int start = 6;
    size_t len = 5;

    char *result = ft_substr(str, start, len);
    if (result) {
        printf("ft_substr: '%s'\n", result); // Expected: "World"
        free(result); // Remember to free the allocated memory
    } else {
        printf("ft_substr: NULL returned\n");
    }

    return 0;
}
*/
