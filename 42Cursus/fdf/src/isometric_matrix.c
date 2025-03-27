/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:34:57 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/27 12:56:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion que calcula la proyecccion isometrica x sin transformar*/
static float	*proj_iso_x(t_pixel_data *map_points, int len)
{
	int		x;
	int		y;
	int		i;
	float	*iso_x;

	i = 0;
	iso_x = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		x = 12 * map_points[i].x;
		y = 12 * map_points[i].y;
		iso_x[i] = (x - y) * cos(M_PI / 6);
		i++;
	}
	return (iso_x);
}

/*Funcion que calcula la proyeccion isometrica y sin transformar*/
static float	*proj_iso_y(t_pixel_data *map_points, int len)
{
	int		x;
	int		y;
	int		z;
	int		i;
	float	*iso_y;

	i = 0;
	iso_y = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		x = 12 * map_points[i].x;
		y = 12 * map_points[i].y;
		z = map_points[i].z;
		iso_y[i] = (-1) * (z) + (x + y) * sin(M_PI / 6);
		i++;
	}
	return (iso_y);
}

/*Funcion que transforma las proyecciones isometricas con proporcion en eje x*/
static void	mat_prop_x(t_image_data *img, t_proj_data data, float *x, float *y)
{
	int		i;
	float	dx;
	float	sy;
	float	new_x;
	float	new_y;

	i = 0;
	dx = data.max_iso_x - data.min_iso_x;
	sy = data.max_iso_y + data.min_iso_y;
	while (i < img->len)
	{
		new_x = 1 + 38.0 * (x[i] - data.min_iso_x) / dx;
		new_y = (19.0 * WIDTH) * (2 * y[i] - sy) / (40.0 * dx);
		img->map[i].iso_x = (int)(WIDTH * new_x / 40.0);
		img->map[i].iso_y = (int)(new_y + (HEIGHT / 2));
		i++;
	}
}

/*Funcion que transforma las proyecciones isometricas con proporcion en eje y*/
static void	mat_prop_y(t_image_data *img, t_proj_data data, float *x, float *y)
{
	int		i;
	float	dy;
	float	sx;
	float	new_x;
	float	new_y;

	i = 0;
	dy = data.max_iso_y - data.min_iso_y;
	sx = data.max_iso_x + data.min_iso_x;
	while (i < img->len)
	{
		new_x = (19.0 * HEIGHT) * (2 * x[i] - sx) / (40.0 * dy);
		new_y = 1 + 38.0 * (y[i] - data.min_iso_y) / dy;
		img->map[i].iso_y = (int)(HEIGHT * new_y / 40.0);
		img->map[i].iso_x = (int)(new_x + (WIDTH / 2));
		i++;
	}
}

/*Funcion para calcular las proyecciones isometricas de una matriz de puntos*/
void	iso_matrix(t_image_data *image)
{
	t_proj_data	data;
	float		*iso_x;
	float		*iso_y;
	float		prop_x;
	float		prop_y;

	iso_x = proj_iso_x(image->map, image->len);
	iso_y = proj_iso_y(image->map, image->len);
	data.max_iso_x = ft_max_float(iso_x, image->len);
	data.min_iso_x = ft_min_float(iso_x, image->len);
	data.max_iso_y = ft_max_float(iso_y, image->len);
	data.min_iso_y = ft_min_float(iso_y, image->len);
	prop_x = (data.max_iso_x - data.min_iso_x) / WIDTH;
	prop_y = (data.max_iso_y - data.min_iso_y) / HEIGHT;
	if (prop_x > prop_y)
		mat_prop_x(image, data, iso_x, iso_y);
	else
		mat_prop_y(image, data, iso_x, iso_y);
	free(iso_x);
	free(iso_y);
}
