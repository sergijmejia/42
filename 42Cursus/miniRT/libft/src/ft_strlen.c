/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:58:29 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 17:21:44 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

// Function to compute the length of a string.
// PARAMETERS:
// - const char *s: The input string to be measured.
// DESCRIPTION:
// - This function counts the characters in the string until the null terminator
//   is encountered.
// OUTPUT:
// - Returns the length of the string.
size_t	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
/*
#include <stdio.h>
#include "libft.h"
int main() {
    const char *s = "Hello, World!";

    size_t length = ft_strlen(s);
    printf("Length of string: %zu\n", length);

    return 0;
}
*/
