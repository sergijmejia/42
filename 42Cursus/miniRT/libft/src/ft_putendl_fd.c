/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:10:21 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 11:50:42 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

// Function to write a string and a newline to a specified file descriptor.
// PARAMETERS:
// - char *s: The string to write. If NULL, the function does nothing.
// - int fd: The file descriptor to which the string will be written.
// DESCRIPTION:
// - This function first checks if the string s is NULL. If it is not NULL,
//   it calls ft_putstr_fd to write the string to the specified file descriptor,
//   followed by a newline character written using ft_putchar_fd.
// OUTPUT:
// - This function does not return a value. If s is NULL, no action is taken.
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/*
#include <stdio.h>
int main(void)
{
    int fd = 1; // Standard output
    char *str = "Hello, World!";
    ft_putendl_fd(str, fd);

    return 0;
}
*/
