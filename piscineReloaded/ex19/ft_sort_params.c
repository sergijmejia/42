/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:21:51 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/13 17:11:16 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <unistd.h>
*/
void	ft_putchar(char c);
/*{
	write(1, &c, 1);
}*/

//Es necesario comparar cada uno de los argumentos 
//Para ver cual es el mayor y cual es el menor
//Esto se hace con la funcion desarrollada en el ejercicio ex17: ft_strcmp
int	ft_strcmp(char *s1, char *s2)
{
	int	n;

	n = 0;
	while ((*s1 == *s2) && (*s1 != '\0'))
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
	{
		n = *s1 - *s2;
		return (n);
	}
}

//Pudiendo hacer la comparacion se tienen que organizar 
//En orden ascendente los argumentos.
//Esto se hace mediante el metodo burbuja
void	ft_bubble_char_sort(int n, char *argv[])
{
	int		i;
	int		j;
	char	*aux;

	i = 1;
	while (i <= n - 1)
	{
		j = n - 1;
		while (j >= i)
		{
			if (ft_strcmp(argv[j], argv[j - 1]) < 0)
			{
				aux = argv[j];
				argv[j] = argv[j - 1];
				argv[j - 1] = aux;
			}
			j--;
		}
		i++;
	}
}

//Una vez organizadas hace falta imprimir cada uno de los argumentos. 
//Esto se hace con la funcion del ejercicio ex18: ft_print_params
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
	ft_bubble_char_sort(argc, argv);
	while (n < argc)
	{
		ft_print_params(argv[n]);
		n++;
	}
	return (0);
}
