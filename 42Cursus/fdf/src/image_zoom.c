/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_zoom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:34:39 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/01 18:44:26 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion de error en zoom*/
static void	zoom_error(t_image_data *image)
{
	perror("Error en zoom");
	mlx_close_window(image->mlx);
	end_image(image);
	mlx_terminate(image->mlx);
	exit(EXIT_FAILURE);
}

/*Funcion que establece las nuevas coordenadas en perspectiva*/
static void	set_zoom_pers(t_image_data *image, double del, int32_t x, int32_t y)
{
	t_pixel_data	*new_map;
	int				i;

	new_map = copy_map(image->map, image->len);
	i = 0;
	while ((i < image->len) && new_map)
	{
		if (del > 0)
		{
			new_map[i].pers_x = (image->map[i].pers_x - x) * (1.1 * del) + x;
			new_map[i].pers_y = (image->map[i].pers_y - y) * (1.1 * del) + y;
		}
		else if (del < 0)
		{
			new_map[i].pers_x = (image->map[i].pers_x - x) / (-1.1 * del) + x;
			new_map[i].pers_y = (image->map[i].pers_y - y) / (-1.1 * del) + y;
		}
		i++;
	}
	free(image->map);
	mlx_delete_image(image->mlx, image->img_pers);
	image->map = new_map;
	image->img_pers = mlx_new_image(image->mlx, WIDTH, HEIGHT);
}

/*Funcion que establece las nuevas coordenadas en isometrico*/
static void	set_zoom_iso(t_image_data *image, double del, int32_t x, int32_t y)
{
	t_pixel_data	*new_map;
	int				i;

	new_map = copy_map(image->map, image->len);
	i = 0;
	while ((i < image->len) && new_map)
	{
		if (del > 0)
		{
			new_map[i].iso_x = (image->map[i].iso_x - x) * (1.1 * del) + x;
			new_map[i].iso_y = (image->map[i].iso_y - y) * (1.1 * del) + y;
		}
		else if (del < 0)
		{
			new_map[i].iso_x = (image->map[i].iso_x - x) / (-1.1 * del) + x;
			new_map[i].iso_y = (image->map[i].iso_y - y) / (-1.1 * del) + y;
		}
		i++;
	}
	free(image->map);
	mlx_delete_image(image->mlx, image->img_iso);
	image->map = new_map;
	image->img_iso = mlx_new_image(image->mlx, WIDTH, HEIGHT);
}

/*Funcion que gestiona el zoom de la imagen*/
static void	execute_zoom(t_image_data *image, double del, int32_t x, int32_t y)
{
	if (image->iso_pers)
	{
		set_zoom_pers(image, del, x, y);
		if (!image->map)
			zoom_error(image);
		draw_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_pers, 0, 0);
	}
	else
	{
		set_zoom_iso(image, del, x, y);
		if (!image->map)
			zoom_error(image);
		draw_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
	}
}

/*Funcion para verificar el elapsed time en el zoom para evitar sobrecarga de
memoria*/
void	ft_zoom(t_image_data *image, double delta, int32_t x, int32_t y)
{
	static struct timespec	lst_t;
	struct timespec			curr_t;
	double					t;

	clock_gettime(CLOCK_MONOTONIC, &curr_t);
	t = (curr_t.tv_sec - lst_t.tv_sec) + (curr_t.tv_nsec - lst_t.tv_nsec) / 1e9;
	if (t >= 1.0 / 60.0)
	{
		execute_zoom(image, delta, x, y);
		clock_gettime(CLOCK_MONOTONIC, &lst_t);
	}
}
