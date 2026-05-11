/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:00:26 by rafaguti          #+#    #+#             */
/*   Updated: 2025/04/28 10:05:18 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stddef.h>

// Function to trim characters from the beginning and end of a string.
// PARAMETERS:
// - char const *s1: The string to be trimmed.
// - char const *set: The characters to be trimmed.
// DESCRIPTION:
// - This function trims characters specified in 'set' from the beginning and
//   end of the string 's1'. If the string is NULL or the set is NULL,
//   it returns NULL. If the set is empty, a duplicate of 's1' is returned.
// OUTPUT:
// - Returns a new string with the trimmed content, or NULL on failure.
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed = ft_substr(s1, start, end - start);
	return (trimmed);
}
/*
#include <stdio.h>
#include <string.h>
int main() {
    const char *str = "   Hello World!   ";
    const char *set = " ";

    char *result = ft_strtrim(str, set);
    if (result) {
        printf("ft_strtrim: '%s'\n", result); // Expected: "Hello World!"
        free(result); // Remember to free the allocated memory
    } else {
        printf("ft_strtrim: NULL returned\n");
    }

    return 0;
}
*/
