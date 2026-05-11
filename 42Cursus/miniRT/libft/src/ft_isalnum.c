/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:50:16 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 19:03:29 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if the character is alphanumeric (a letter or a digit)
// PARAMETERS:
// - int c: The character to be checked, passed as an integer.
// DESCRIPTION:
// - This function returns a non-zero value (true) if the character is
//   either a letter (uppercase or lowercase) or a digit (0-9).
// - It returns zero (false) if the character is not alphanumeric.
// OUTPUT:
// - Returns non-zero if true, zero otherwise.
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
/*
#include <stdio.h>
int main(void)
{
    char tests[] = {'A', '1', '!', ' ', '\0', 'z'};

    printf("Test ft_isalnum\n");
    for (int i = 0; i < sizeof(tests); i++)
    {
        printf("Character: '%c' -> ft_isalnum: %d\n",
				tests[i], ft_isalnum(tests[i]));
    }
    return 0;
}
*/
