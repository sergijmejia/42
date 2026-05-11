/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:10:49 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 16:42:48 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>

// Helper function to write a long integer to a specified file descriptor.
// PARAMETERS:
// - long n: The long integer to write.
// - int fd: The file descriptor to which the integer will be written.
// DESCRIPTION:
// - This function uses recursion to write each digit of the integer n to the
//   specified file descriptor, starting from the most significant digit.
// OUTPUT:
// - This function does not return a value.
static void	ft_write_nbr(long n, int fd)
{
	if (n >= 10)
		ft_write_nbr(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

// Function to write an integer to a specified file descriptor.
// PARAMETERS:
// - int n: The integer to write.
// - int fd: The file descriptor to which the integer will be written.
// DESCRIPTION:
// - This function converts the integer n into a string representation and
//   writes it to the specified file descriptor fd. If n is negative, it first
//   writes a minus sign and then handles the absolute value of n.
// OUTPUT:
// - This function does not return a value.
void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	ft_write_nbr(num, fd);
}
/*
#include <stdio.h>
int main(void)
{
    int fd = 1; // Standard output
    ft_putnbr_fd(42, fd);
    ft_putchar_fd('\n', fd);
    ft_putnbr_fd(-42, fd);
    ft_putchar_fd('\n', fd);

    return 0;
}
*/
