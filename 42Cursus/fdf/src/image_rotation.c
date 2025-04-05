/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:30 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/04 10:08:19 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que establece las nuevas coordenadas en isometrico*/
static void	set_rt_iso(t_image_data *image, int32_t *xy, double theta)
{
	int		i;
	double	x_rel;
	double	y_rel;

	i = 0;
	while (i < image->len)
	{
		x_rel = image->map[i].iso_x - xy[0];
		y_rel = image->map[i].iso_y - xy[1];
		image->map[i].iso_x = x_rel * cos(theta) - y_rel * sin(theta) + xy[0];
		image->map[i].iso_y = x_rel * sin(theta) + y_rel * cos(theta) + xy[1];
		i++;
	}
}

/*Funcion que establece las nuevas coordenadas en perspectiva*/
static void	set_rt_pers(t_image_data *image, int32_t *xy, double theta)
{
	int		i;
	double	x_rel;
	double	y_rel;

	i = 0;
	while (i < image->len)
	{
		x_rel = image->map[i].pers_x - xy[0];
		y_rel = image->map[i].pers_y - xy[1];
		image->map[i].pers_x = x_rel * cos(theta) - y_rel * sin(theta) + xy[0];
		image->map[i].pers_y = x_rel * sin(theta) + y_rel * cos(theta) + xy[1];
		i++;
	}
}

/*Funcion para definir el angulo de rotacion*/
static double	rt_angle(t_image_data *image, double x, double y, int32_t *xy)
{
	static double	theta0_mod;
	double			theta[2];

	if (image->start_rotation == 1)
	{
		if (image->mod == 1)
			mlx_get_mouse_pos(image->mlx, &xy[0], &xy[1]);
		else
		{
			xy[0] = WIDTH / 2;
			xy[1] = HEIGHT / 2;
		}
		image->start_rotation = 0;
		theta0_mod = 0.0;
	}
	if (image->mod == 1)
		theta[0] = theta0_mod;
	else
		theta[0] = atan2(image->old_y - xy[1], image->old_x - xy[0]);
	theta[1] = atan2(y - xy[1], x - xy[0]);
	if (image->mod == 1)
		theta0_mod = theta[1];
	return (theta[1] - theta[0]);
}

/*Funcion para realizar la rotacion respecto al movimiento del cursor*/
static void	execute_rotation(t_image_data *image, double xpos, double ypos)
{
	static int32_t	xy[2];
	double			theta;

	theta = rt_angle(image, xpos, ypos, &xy[0]);
	image->old_x = (int32_t) xpos;
	image->old_y = (int32_t) ypos;
	draw_map(image, 1);
	if (image->iso_pers)
		set_rt_pers(image, &xy[0], theta);
	else
		set_rt_iso(image, &xy[0], theta);
	draw_map(image, 0);
}

/*Funcion para verificar el elapsed time de la rotacion para evitar sobrecarga
de memoria*/
void	ft_image_rotation(t_image_data *image, double xpos, double ypos)
{
	static struct timespec	lst_t;
	struct timespec			curr_t;
	double					t;

	clock_gettime(CLOCK_MONOTONIC, &curr_t);
	t = (curr_t.tv_sec - lst_t.tv_sec) + (curr_t.tv_nsec - lst_t.tv_nsec) / 1e9;
	if (t >= 1.0 / 60.0)
	{
		execute_rotation(image, xpos, ypos);
		clock_gettime(CLOCK_MONOTONIC, &lst_t);
	}
}
