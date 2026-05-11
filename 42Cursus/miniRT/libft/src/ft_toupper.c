/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:17:08 by rafaguti          #+#    #+#             */
/*   Updated: 2024/09/15 00:27:20 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function to convert a lowercase letter to uppercase.
// PARAMETERS:
// - int c: The character to convert.
// DESCRIPTION:
// - This function checks if the character 'c' is a lowercase letter. If it
//   is, the corresponding uppercase character is returned. If not, 'c' is
//   returned unchanged.
// OUTPUT:
// - Returns the uppercase equivalent of 'c', or 'c' if it is not lowercase.
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
/*
#include <stdio.h>
int main() {
    char ch = 'a';

    int upper = ft_toupper(ch);
    printf("ft_toupper: '%c' -> '%c'\n", ch, upper); // Expected: 'A'

    return 0;
}
*/
