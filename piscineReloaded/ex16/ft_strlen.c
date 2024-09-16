/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:22:26 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 12:30:39 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
*/
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
/*
int	main(int argc, char *argv[])
{
	int	n;

	if (argc != 2)
		return (1);
	n = ft_strlen(argv[1]);
	printf("La longitud es de %d caracteres \n", n);
	return (0);
}
*/
