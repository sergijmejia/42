/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:48:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/05 01:44:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "libft.h"
#include <stdio.h>

void	prueba(unsigned int i, char *c)
{
	(void)i;
	if ((*c >= 97) && (*c <= 122))
		*c = *c - ('a' - 'A');
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	char			*c;

	i = 0;
	while (s[i] != '\0')
	{
		c = &s[i];
		f(i, c);
		i++;
	}
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	printf("El string orignal es: %s\n", argv[1]);
	ft_striteri(argv[1], prueba);
	printf("El string despues de ft_striteri es: %s\n", argv[1]);
	return (0);
}
*/
