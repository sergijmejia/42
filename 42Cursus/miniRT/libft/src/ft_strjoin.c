/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:59:22 by rafaguti          #+#    #+#             */
/*   Updated: 2024/09/21 01:47:20 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

// Function to join two strings into a new string.
// PARAMETERS:
// - char const *s1: The first input string.
// - char const *s2: The second input string.
// DESCRIPTION:
// - This function allocates memory for a new string, copies the first
//   string and then concatenates the second string to it.
// OUTPUT:
// - Returns a pointer to the new string or NULL on failure.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 + len2 < len1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcat(str, s2, len1 + len2 + 1);
	return (str);
}
/*
#include <stdio.h>
int main() {
    const char *s1 = "Hello, ";
    const char *s2 = "World!";

    char *joined = ft_strjoin(s1, s2);
    if (joined) {
        printf("Joined string: %s\n", joined);
        free(joined); // Free the joined string
    } else {
        printf("Failed to join strings.\n");
    }

    return 0;
}
*/
