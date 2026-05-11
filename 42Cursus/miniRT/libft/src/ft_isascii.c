/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:12 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 19:03:46 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if the character is an ASCII character (0-127).
// PARAMETERS:
// - int c: The character to be checked, passed as an integer.
// DESCRIPTION:
// - This function returns a non-zero value (true) if the character is within
//   the ASCII range (0 to 127).
// - It returns zero (false) if the character is outside this range.
// OUTPUT:
// - Returns non-zero if true, zero otherwise.
int	ft_isascii(int c)
{
	return ((c >= 0) && (c <= 127));
}
/*
#include <stdio.h>
int main(void)
{
    char tests[] = {'A', 128, 'z', -1};

    printf("Test ft_isascii\n");
    for (int i = 0; i < sizeof(tests); i++)
    {
        printf("Character: '%d' -> ft_isascii: %d\n",
				tests[i], ft_isascii(tests[i]));
    }
    return 0;
}
*/
