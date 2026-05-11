/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:07:36 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 19:03:14 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if the character is alphabetic (A-Z or a-z).
// PARAMETERS:
// - int c: The character to be checked, passed as an integer.
// DESCRIPTION:
// - This function returns a non-zero value (true) if the character is
//   an uppercase letter (A-Z) or a lowercase letter (a-z).
// - It returns zero (false) if the character is not alphabetic.
// OUTPUT:
// - Returns non-zero if true, zero otherwise.
int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
/*
#include <stdio.h>
int main(void)
{
    char tests[] = {'A', '1', '!', ' ', 'z', '\0'};

    printf("Test ft_isalpha\n");
    for (int i = 0; i < sizeof(tests); i++)
    {
        printf("Character: '%c' -> ft_isalpha: %d\n",
				tests[i], ft_isalpha(tests[i]));
    }
    return 0;
}
*/
