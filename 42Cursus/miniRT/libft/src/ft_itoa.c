/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:03:11 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 22:01:24 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

// Helper function to calculate the length of the number string.
// PARAMETERS:
// - int n: The integer whose length is to be calculated.
// DESCRIPTION:
// - This function returns the number of characters needed to represent the
//   integer, including the sign if it's negative.
static int	ft_numlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

// Helper function to convert the number into a string.
// PARAMETERS:
// - int n: The integer to be converted.
// - char *str: A pointer to the string buffer where the number will be stored.
// DESCRIPTION:
// - This function handles negative numbers by using unsigned int to avoid
//   overflow. It recursively fills the string with digits from left to right.
static char	*ft_putnbr_str(int n, char *str)
{
	unsigned int	num;

	if (n < 0)
	{
		*str++ = '-';
		num = (unsigned int)-n;
	}
	else
	{
		num = (unsigned int)n;
	}
	if (num >= 10)
		str = ft_putnbr_str(num / 10, str);
	*str++ = (num % 10) + '0';
	return (str);
}

// Main function to convert an integer to a null-terminated string.
// PARAMETERS:
// - int n: The integer to be converted.
// DESCRIPTION:
// - This function handles the edge case for INT_MIN specifically.
// - It uses ft_numlen to determine the length of the string.
// - It allocates memory for the string and returns NULL if allocation fails.
// - It uses ft_putnbr_str to fill the string with digits.
char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_putnbr_str(n, str);
	return (str);
}
/*
#include <stdio.h>
int main(void)
{
    int test_values[] = {123, -123, 0, INT_MAX, INT_MIN};

    printf("Test ft_itoa\n");
    for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++)
    {
        char *result = ft_itoa(test_values[i]);
        printf("Value: %d -> ft_itoa: %s\n", test_values[i], result);
        free(result);
    }
    return 0;
}
*/
