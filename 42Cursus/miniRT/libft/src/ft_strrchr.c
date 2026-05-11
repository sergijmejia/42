/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:25:29 by rafaguti          #+#    #+#             */
/*   Updated: 2024/09/16 23:14:04 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function to locate the last occurrence of a character in a string.
// PARAMETERS:
// - const char *s: The string to be searched.
// - int c: The character to locate.
// DESCRIPTION:
// - This function searches for the last occurrence of the character 'c'
//   in the string 's'. If found, a pointer to the character in 's' is returned
// OUTPUT:
// - Returns a pointer to last occurrence of the character or NULL if not found
char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	char	*last;

	p = (char *)s;
	last = 0;
	while (*p != '\0')
	{
		if (*p == (char)c)
			last = p;
		p++;
	}
	if (*p == (char)c)
		return (p);
	return (last);
}
/*
#include <stdio.h>
int main() {
    const char *str = "Hello World!";
    int ch = 'o';

    char *result = ft_strrchr(str, ch);
    if (result) {
        printf("ft_strrchr: Last occurrence of '%c' found at: %s\n", ch, result);
    } else {
        printf("ft_strrchr: Character not found\n");
    }

    return 0;
}
*/
