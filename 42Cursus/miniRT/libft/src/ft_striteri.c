/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:05:50 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 16:45:15 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

// Function to apply a function to each character of a string.
// PARAMETERS:
// - char *s: The input string to be modified.
// - void (*f)(unsigned int, char*): The function to apply to each character.
// DESCRIPTION:
// - This function iterates through each character of the string, applying
//   the specified function to each character along with its index.
// OUTPUT:
// - Returns nothing; modifies the string in place.
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>
// Function to modify each character (example: convert to uppercase)
void to_uppercase(unsigned int i, char *c) {
    if (*c >= 'a' && *c <= 'z') {
        *c -= 32; // Convert to uppercase
    }
}

int main() {
    char str[] = "Hello, World!";

    ft_striteri(str, to_uppercase);
    printf("Modified string: %s\n", str);

    return 0;
}
*/
