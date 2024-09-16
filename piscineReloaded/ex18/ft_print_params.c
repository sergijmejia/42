/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:57:40 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 16:25:59 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <unistd.h>
*/
void	ft_putchar(char c);
/*{
	write(1, &c, 1);
}*/

void	ft_print_params(char *str)
{
	if (*str == '\0')
	{
		ft_putchar('\n');
		return ;
	}
	ft_putchar(*str);
	str++;
	ft_print_params(str);
}

int	main(int argc, char *argv[])
{
	int	n;

	n = 1;
	while (n < argc)
	{
		ft_print_params(argv[n]);
		n++;
	}
	return (0);
}
