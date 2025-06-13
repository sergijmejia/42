/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:48:00 by smejia-a          #+#    #+#             */
/*   Updated: 2025/06/08 14:33:24 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Este es un programa para ir testeand tods los componentes*/
int	main(int argc, char **argv)
{
	t_list	*lst;
	if (argc != 2)
	{
		ft_printf("Cantidad de argumentos invalida\n");
		return(EXIT_FAILURE);
	}
	lst = NULL;
	quote_divider(&lst, argv[1]);
	printf("La longitud de lst es: %d\n", ft_lstsize(lst));
	print_lst(lst);
	exit(EXIT_SUCCESS);
}
