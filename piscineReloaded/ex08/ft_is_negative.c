/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:02:23 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/12 18:57:14 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
//#include <stdlib.h>

void	ft_putchar(char c);
/*{
	write(1, &c, 1);
}
*/

void	ft_is_negative(int n)
{
	char	c;

	if (n < 0)
	{
		c = 'N';
		ft_putchar(c);
	}
	else
	{
		c = 'P';
		ft_putchar(c);
	}
}
/*
int	main(int argc, char *argv[])
{
	int	n;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	ft_is_negative(n);
	return (0);
}
*/
