/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:25 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 12:15:22 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <unistd.h>
*/
void	ft_putchar(char c);
/*{
	write(1, &c, 1);
}
*/

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		ft_putchar(*str);
		str++;
	}
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	ft_putstr(argv[1]);
	return (0);
}
*/
