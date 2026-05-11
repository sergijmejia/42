/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:57:16 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 11:45:52 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"

// Sets the first n bytes of the memory area pointed to by s to zero
// PARAMETERS:
// - void *s: Pointer to the memory area to be zeroed
// - size_t n: Number of bytes to set to zero
// DESCRIPTION:
// - It fills the first n bytes of the memory area pointed to by s with zeros.
// - This effectively nullifies the specified portion of memory.
// - It is equivalent to calling ft_memset with '\0' as the character to set.
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
    char str[10] = "Hello";

    printf("Test ft_bzero\n");
    printf("Original string: \"%s\"\n", str);
    ft_bzero(str, 3);
    printf("After ft_bzero(3): \"%s\"\n", str);
    return 0;
}
*/
