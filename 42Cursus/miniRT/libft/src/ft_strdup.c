/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:16:53 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/31 11:05:02 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// Function to duplicate a string.
// PARAMETERS:
// - const char *s: The input string to be duplicated.
// DESCRIPTION:
// - This function allocates memory for a new string, copies the input string
//   into it, and returns a pointer to the new string.
// OUTPUT:
// - Returns a pointer to the duplicated string or NULL on failure.
char	*ft_strdup(const char *s)
{
	unsigned int	i;
	unsigned int	len;
	char			*dst;

	len = ft_strlen(s);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
#include <stdio.h>
int main() {
    const char *s = "Hello, World!";

    char *dup = ft_strdup(s);
    if (dup) {
        printf("Original: %s\nDuplicated: %s\n", s, dup);
        free(dup); // Free the duplicated string
    } else {
        printf("Failed to duplicate the string.\n");
    }

    return 0;
}
*/
