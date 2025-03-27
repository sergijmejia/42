/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:59:22 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/27 15:07:44 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion que calcula la proyecccion con perspectiva x sin transformar*/
static float	*proj_pers_x(t_pixel_data *map_points, int len, double d)
{
	float	x;
	float	z;
	int		i;
	float	c_xyz[3];
	float	*pers_x;

	i = 0;
	c_xyz[0] = -650;
	c_xyz[2] = 10000;
	pers_x = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		x = (float) map_points[i].x;
		z = (float) map_points[i].z;
		if (z == c_xyz[2])
			pers_x[i] = 4 * (x - c_xyz[0]) * d;
		else
			pers_x[i] = ((x - c_xyz[0]) / (c_xyz[2] - z)) * d;
		i++;
	}
	return (pers_x);
}

/*Funcion que calcula la proyeccion isometrica y sin transformar*/
static float	*proj_pers_y(t_pixel_data *map_points, int len, double d)
{
	float	y;
	float	z;
	int		i;
	float	c_xyz[3];
	float	*pers_y;

	i = 0;
	c_xyz[1] = 2250;
	c_xyz[2] = 10000;
	pers_y = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		y = (float) map_points[i].y;
		z = (float) map_points[i].z;
		if (z == c_xyz[2])
			pers_y[i] = 4 * (y - c_xyz[1]) * d;
		else
			pers_y[i] = ((y - c_xyz[1]) / (c_xyz[2] - z)) * d;
		i++;
	}
	return (pers_y);
}

/*Funcion que transforma las proyecciones en perspectiva en eje x*/
static void	mat_prop_x(t_image_data *img, t_proj_data data, float *x, float *y)
{
	int		i;
	float	dx;
	float	sy;
	float	new_x;
	float	new_y;

	i = 0;
	dx = data.max_pers_x - data.min_pers_x;
	sy = data.max_pers_y + data.min_pers_y;
	while (i < img->len)
	{
		new_x = 1 + 38.0 * (x[i] - data.min_pers_x) / dx;
		new_y = (19.0 * WIDTH) * (2 * y[i] - sy) / (40.0 * dx);
		img->map[i].pers_x = (int)(WIDTH * new_x / 40.0);
		img->map[i].pers_y = (int)(new_y + (HEIGHT / 2));
		i++;
	}
}

/*Funcion que transforma las proyecciones en perspectiva en eje y*/
static void	mat_prop_y(t_image_data *img, t_proj_data data, float *x, float *y)
{
	int		i;
	float	dy;
	float	sx;
	float	new_x;
	float	new_y;

	i = 0;
	dy = data.max_pers_y - data.min_pers_y;
	sx = data.max_pers_x + data.min_pers_x;
	while (i < img->len)
	{
		new_x = (19.0 * HEIGHT) * (2 * x[i] - sx) / (40.0 * dy);
		new_y = 1 + 38.0 * (y[i] - data.min_pers_y) / dy;
		img->map[i].pers_y = (int)(HEIGHT * new_y / 40.0);
		img->map[i].pers_x = (int)(new_x + (WIDTH / 2));
		i++;
	}
}

/*Funcion para calcular las proyecciones conicas de una matriz de puntos*/
void	perspective_matrix(t_image_data *image, double d_projection)
{
	t_proj_data	data;
	float		*pers_x;
	float		*pers_y;
	float		prop_x;
	float		prop_y;

	pers_x = proj_pers_x(image->map, image->len, d_projection);
	pers_y = proj_pers_y(image->map, image->len, d_projection);
	data.max_pers_x = ft_max_float(pers_x, image->len);
	data.min_pers_x = ft_min_float(pers_x, image->len);
	data.max_pers_y = ft_max_float(pers_y, image->len);
	data.min_pers_y = ft_min_float(pers_y, image->len);
	prop_x = (data.max_pers_x - data.min_pers_x) / WIDTH;
	prop_y = (data.max_pers_y - data.min_pers_y) / HEIGHT;
	if (prop_x > prop_y)
		mat_prop_x(image, data, pers_x, pers_y);
	else
		mat_prop_y(image, data, pers_x, pers_y);
	free(pers_x);
	free(pers_y);
}
