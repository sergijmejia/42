/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:58:03 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/05 12:33:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Error en la lectura del archivo*/
void	error_file(char *line)
{
	if (line == NULL)
	{
		write(2, "Error reading file\n", 19);
		exit(EXIT_FAILURE);
	}
}
