/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:05:59 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/31 12:14:10 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion para manejar los errores*/
void	end_image(t_image_data *image)
{
	free(image->iso_x_moved);
	free(image->iso_y_moved);
	free(image->map);
	free(image->home_map);
	mlx_delete_image(image->mlx, image->img_iso);
	mlx_delete_image(image->mlx, image->img_pers);
}

/*Funcion para copiar la memoria de un mapa a otro*/
t_pixel_data	*copy_map(t_pixel_data *map_points, int len)
{
	int				i;
	t_pixel_data	*new_map_points;

	new_map_points = (t_pixel_data *) malloc (sizeof(t_pixel_data) * len);
	if (!new_map_points)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_map_points[i] = map_points[i];
		i++;
	}
	return (new_map_points);
}

/*Funcion para encontrar el valor maximo de un array de float*/
float	ft_max_float(float *cord, int len)
{
	float	max;
	int		i;

	max = cord[0];
	i = 0;
	while (i < len)
	{
		if (cord[i] > max)
			max = cord[i];
		i++;
	}
	return (max);
}

/*Funcion para encontrar el valor minimo de un array de flat*/
float	ft_min_float(float *cord, int len)
{
	float	min;
	int		i;

	min = cord[0];
	i = 0;
	while (i < len)
	{
		if (cord[i] < min)
			min = cord[i];
		i++;
	}
	return (min);
}

/*Funcion de libearacion de memoria del split*/
char	*ft_clean_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}
