/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:04:14 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 16:45:45 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

// Function to create a new string by applying a function to each character.
// PARAMETERS:
// - char const *s: The input string to be transformed.
// - char (*f)(unsigned int, char): The function to apply to each character.
// DESCRIPTION:
// - This function allocates memory for a new string, applies the specified
//   function to each character of the input string, and stores the result.
// OUTPUT:
// - Returns a pointer to the new string or NULL on failure.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*result;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
#include <stdio.h>
// Function to convert each character to uppercase
char to_uppercase(unsigned int i, char c) {
    return (c >= 'a' && c <= 'z') ? c - 32 : c;
}

int main() {
    const char *s = "Hello, World!";

    char *modified = ft_strmapi(s, to_uppercase);
    if (modified) {
        printf("Modified string: %s\n", modified);
        free(modified); // Free the modified string
    } else {
        printf("Failed to create modified string.\n");
    }

    return 0;
}
*/
