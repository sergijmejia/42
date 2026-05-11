/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:28:37 by rafaguti          #+#    #+#             */
/*   Updated: 2024/09/15 00:29:25 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function to convert an uppercase letter to lowercase.
// PARAMETERS:
// - int c: The character to convert.
// DESCRIPTION:
// - This function checks if the character 'c' is an uppercase letter. If it
//   is, the corresponding lowercase character is returned. If not, 'c' is
//   returned unchanged.
// OUTPUT:
// - Returns the lowercase equivalent of 'c', or 'c' if it is not uppercase.
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
/*
#include <stdio.h>
int main() {
    char ch = 'A';

    int lower = ft_tolower(ch);
    printf("ft_tolower: '%c' -> '%c'\n", ch, lower); // Expected: 'a'

    return 0;
}
*/
