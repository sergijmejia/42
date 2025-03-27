/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_traslation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:07:19 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/27 18:33:00 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion que establece las nuevas coordenadas en isometrico*/
static void	set_rt_iso(t_image_data *image, double dx, double dy)
{
	int		i;

	i = 0;
	while (i < image->len)
	{
		image->map[i].iso_x = image->map[i].iso_x + dx;
		image->map[i].iso_y = image->map[i].iso_y + dy;
		i++;
	}
}

/*Funcion que establece las nuevas coordenadas en perspectiva*/
static void	set_rt_pers(t_image_data *image, double dx, double dy)
{
	int		i;

	i = 0;
	while (i < image->len)
	{
		image->map[i].pers_x = image->map[i].pers_x + dx;
		image->map[i].pers_y = image->map[i].pers_y + dy;
		i++;
	}
}

/*Funcion para realizar la traslacion respecto al movimiento del cursor*/
void	execute_traslation(t_image_data *image, double xpos, double ypos)
{
	double	dx;
	double	dy;

	dx = xpos - image->old_x;
	dy = ypos - image->old_y;
	image->old_x = (int32_t) xpos;
	image->old_y = (int32_t) ypos;
	clear_image(image);
	if (image->iso_pers)
		set_rt_pers(image, dx, dy);
	else
		set_rt_iso(image, dx, dy);
	draw_map(image, 0);
}

/*Funcion para verificar el elapsed time de la traslacion para evitar sobrecarga
de memoria*/
void	ft_image_traslation(t_image_data *image, double xpos, double ypos)
{
	static struct timespec	lst_t;
	struct timespec			curr_t;
	double					t;

	clock_gettime(CLOCK_MONOTONIC, &curr_t);
	t = (curr_t.tv_sec - lst_t.tv_sec) + (curr_t.tv_nsec - lst_t.tv_nsec) / 1e9;
	if (t >= 1.0 / 60.0)
	{
		execute_traslation(image, xpos, ypos);
		clock_gettime(CLOCK_MONOTONIC, &lst_t);
	}
}
