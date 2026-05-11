/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:08:06 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 19:04:11 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if the character is a decimal digit (0-9).
// PARAMETERS:
// - int c: The character to be checked, passed as an integer.
// DESCRIPTION:
// - This function checks whether the input character falls within the
//   range of decimal digits (ASCII values from '0' to '9').
// OUTPUT:
// - Returns non-zero (true) if the character is a digit, otherwise returns
//   zero (false).
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
#include <stdio.h>
int main(void)
{
    char tests[] = {'0', '5', '9', 'a', ' ', '\0'};

    printf("Test ft_isdigit\n");
    for (int i = 0; i < sizeof(tests); i++)
    {
        printf("Character: '%c' -> ft_isdigit: %d\n",
				tests[i], ft_isdigit(tests[i]));
    }
    return 0;
}
*/
