/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_print_arg_ux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:37:19 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/05 17:56:37 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_create_print_arg_ux(char *s, va_list args, char **arg, char c)
{
	int	len;

	if (c == 'u')
		*arg = ft_unsig_int(s, args);
	if (c == 'x')
		*arg = ft_hexa_num_lower(s, args);
	if (c == 'X')
		*arg = ft_hexa_num_upper(s, args);
	if (!*arg)
		return (-1);
	len = (int) ft_strlen(*arg);
	return (len);
}
