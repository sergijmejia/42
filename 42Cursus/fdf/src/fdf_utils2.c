/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:57:17 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/04 18:23:23 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion para calcular el minimo y el maximo de un mapa*/
void	set_first_min_max(t_image_data *image, char *line)
{
	char	**split_line;
	char	**split_color;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		free(line);
		error_file(line);
	}
	split_color = ft_split(split_line[0], ',');
	if (!split_color)
	{
		ft_clean_split(split_line);
		free(line);
		error_file(line);
	}
	image->min = ft_atoi(split_color[0]);
	image->max = ft_atoi(split_color[0]);
	ft_clean_split(split_color);
	ft_clean_split(split_line);
}

/*Funcionn para obtener el rgb de un hexadecimal*/
void	color_hexa(t_image_data *image, char *color, int i)
{
	char	*one_color;

	one_color = (char *) malloc (sizeof(char *) * 3);
	ft_strlcpy(one_color, &color[0], 3);
	one_color[2] = '\0';
	image->map[i].b = hexa_to_int(one_color, 2);
	ft_strlcpy(one_color, &color[2], 3);
	one_color[2] = '\0';
	image->map[i].g = hexa_to_int(one_color, 2);
	ft_strlcpy(one_color, &color[4], 3);
	image->map[i].r = hexa_to_int(one_color, 2);
	free(one_color);
}
