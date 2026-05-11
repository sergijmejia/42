/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:07:48 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/29 13:04:47 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

// Function to write a character to a specified file descriptor.
// PARAMETERS:
// - char c: The character to write.
// - int fd: The file descriptor to which the character will be written.
// DESCRIPTION:
// - This function uses the write system call to output the character c
//   to the file descriptor fd. It writes exactly one byte.
// OUTPUT:
// - This function does not return a value. Any error in writing is not handled.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <stdio.h>
int main(void)
{
    int fd = 1; // Standard output
    ft_putchar_fd('A', fd);
    ft_putchar_fd('\n', fd);

    return 0;
}
*/
