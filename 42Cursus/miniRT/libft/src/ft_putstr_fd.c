/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:09:01 by rafaguti          #+#    #+#             */
/*   Updated: 2024/10/30 16:43:12 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

// Function to write a string to a specified file descriptor.
// PARAMETERS:
// - char *s: The string to be written.
// - int fd: The file descriptor to which the string will be written.
// DESCRIPTION:
// - This function checks if the input string s is not NULL, and if it is valid
//   it writes the string to the specified file descriptor fd using the write
//   system call.
// OUTPUT:
// - This function does not return a value.
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
/*
#include <stdio.h>
int main(void)
{
    int fd = 1; // Standard output
    char *str = "Hello, World!";
    ft_putstr_fd(str, fd);

    return 0;
}
*/
