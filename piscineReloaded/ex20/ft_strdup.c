/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:21:51 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/16 17:22:20 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
/*#include <stdio.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}*/

int	ft_strlen(char *str)
{
	int	l;

	l = 0;
	while (*str != '\0')
	{
		l++;
		str++;
	}
	return (l);
}

/*void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		ft_putchar(*str);
		str++;
	}
}
*/
char	*ft_strdup(char *src)
{
	char	*new_pointer;
	char	*aux_pointer;

	new_pointer = (char *) malloc ((ft_strlen(src) + 1) * sizeof(char));
	aux_pointer = new_pointer;
	while (*src != '\0')
	{
		*aux_pointer = *src;
		aux_pointer++;
		src++;
	}
	*aux_pointer = '\0';
	return (new_pointer);
}
/*
int	main(int argc, char *argv[])
{
	char	*new_string;

	if (argc != 2)
		return (1);
	new_string = ft_strdup(argv[1]);
	ft_putstr(new_string);
	return (0);
}
*/
