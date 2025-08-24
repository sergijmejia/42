/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:48:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/08/06 18:01:15 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Este es un programa para ir testeand tods los componentes*/
int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	t_list	*lst;

	if (argc != 2)
	{
		ft_printf("Cantidad de argumentos invalida\n");
		return(EXIT_FAILURE);
	}
	lst = NULL;
	fd	= open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		if (check_parentheses_balance(str))
		{
			printf("Error\n");
			return (EXIT_FAILURE);
		}
		quote_divider(&lst, str);
		space_divider(&lst);
		//aqui puedo evaluar si hay comillas vacias y en caso de palabra unica de comillas vacias informar de error y cerrar programa
		special_char_divider(&lst);
		find_command_option(&lst);
		//
		str = get_next_line (fd);
	}
	print_lst(lst);
	exit(EXIT_SUCCESS);
}
