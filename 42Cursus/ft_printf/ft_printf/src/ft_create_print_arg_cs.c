/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_print_arg_cs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:23:49 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/07 19:21:04 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_create_print_arg_cs(char *s, va_list args, char **arg, char c)
{
	int	len;

	c = s[ft_strlen(s) - 1];
	if (c == 'c')
		len = ft_character(s, args, *arg);
	if (c == 's')
	{
		*arg = ft_string(s, args);
		if (!arg)
			return (-1);
		len = (int) ft_strlen(*arg);
	}
	return (len);
}
