/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:12:31 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 19:05:36 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts a string to its integer representation
// PARAMETERS:
// - const char *nptr: Pointer to the string to be converted
// DESCRIPTION:
// 1- It skips any leading whitespace characters (spaces, tabs, newlines, etc.).
// 2- Checks for an optional '+' or '-' sign to determine the sign of the number
// 3- The conversion stops when a non-digit character is encountered.
// 4- Returns the integer value represented by the string, adjusted for sign.
int	ft_atoi(const char *nptr)
{
	int		sign;
	int		result;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	result = 0;
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    const char *tests[] = {
        "123", "-123", "   +123", "0",
        "2147483647", "2147483648", "    -123abc"
    };

    printf("Test ft_atoi\n");
    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        printf("Input: \"%s\"\n", tests[i]);
        printf("\tft_atoi: %d\n", ft_atoi(tests[i]));
        printf("\tatoi   : %d\n", atoi(tests[i]));
    }
    return 0;
}
*/
