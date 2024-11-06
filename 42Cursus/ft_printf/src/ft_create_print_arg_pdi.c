/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_print_arg_pdi.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:30:26 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/05 17:34:33 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_create_print_arg_cs(char *s, va_list args, char **arg, char c)
{
	int	len;

	if (c == 'p')
		*arg = ft_hexa_pointer(s, args);
	if (c == 'd')
		*arg = ft_integer(s, args);
	if (c == 'i')
		*arg = ft_integer(s, args);
	if (!*arg)
		return (-1);
	len = (int) ft_strlen(*arg);
	return (len);
}
