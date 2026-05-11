/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:42 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 19:04:28 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if the character is printable (including space).
// PARAMETERS:
// - int c: The character to be checked, passed as an integer.
// DESCRIPTION:
// - This function determines whether the input character is a printable
//   character in the ASCII table, which includes the range from space (32)
//   to tilde (126).
// OUTPUT:
// - Returns non-zero (true) if the character is printable, otherwise returns
//   zero (false).
int	ft_isprint(int c)
{
	return ((c >= 32) && (c <= 126));
}
/*
#include <stdio.h>
int main(void)
{
    char tests[] = {' ', 'A', '~', '\n', 127};

    printf("Test ft_isprint\n");
    for (int i = 0; i < sizeof(tests); i++)
    {
        printf("Character: '%c' -> ft_isprint: %d\n",
				tests[i], ft_isprint(tests[i]));
    }
    return 0;
}
*/
