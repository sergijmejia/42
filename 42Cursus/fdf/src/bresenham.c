/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:15:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/28 11:04:27 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion que recopila los datos de los puntos p1 y p0 y los almacena en la 
estructura s_line_data*/
static void	line_limits(t_line_data *line, t_pixel_data p0, t_pixel_data p1)
{
	line->x0 = p0.iso_x;
	line->y0 = p0.iso_y;
	line->x1 = p1.iso_x;
	line->y1 = p1.iso_y;
	line->dx = line->x1 - line->x0;
	line->dy = line->y1 - line->y0;
}

/*Funcion que recopila los datos de los avances inclinados y los almacena en
la estructura s_line_data*/
static void	line_inclined(t_line_data *line)
{
	if (line->dx >= 0)
		line->sx_in = 1;
	else
	{
		line->dx = (-1) * line->dx;
		line->sx_in = -1;
	}
	if (line->dy >= 0)
		line->sy_in = 1;
	else
	{
		line->dy = (-1) * line->dy;
		line->sy_in = -1;
	}
}

/*Funcion que recopila los datos de los avances rectos y los almacena en
la estructura s_line_data*/
static void	line_straight(t_line_data *line)
{
	int	i;

	if (line->dx >= line->dy)
	{
		line->sy_st = 0;
		line->sx_st = line->sx_in;
	}
	else
	{
		line->sx_st = 0;
		line->sy_st = line->sy_in;
		i = line->dx;
		line->dx = line->dy;
		line->dy = i;
	}
	line->adv_st = 2 * line->dy;
	line->adv = line->adv_st - line->dx;
	line->adv_in = line->adv - line->dx;
}

/*Funion que aplica el color a cada uno de los pixeles localizados mediane
(x, y)*/
static void	draw_pixel(mlx_image_t *img, t_line_data *line)
{
	int	index;

	index = (line->y0 * img->width + line->x0) * 4;
	if ((index >= 0) && (index < (int)(img->width * img->height * 4)))
	{
		img->pixels[index] = 255;
		img->pixels[index + 1] = 255;
		img->pixels[index + 2] = 255;
		img->pixels[index + 3] = 255;
	}
	if (line->adv >= 0)
	{
		line->x0 = line->x0 + line->sx_in;
		line->y0 = line->y0 + line->sy_in;
		line->adv = line->adv + line->adv_in;
	}
	else
	{
		line->x0 = line->x0 + line->sx_st;
		line->y0 = line->y0 + line->sy_st;
		line->adv = line->adv + line->adv_st;
	}
}

/*Algoritmo de Bresenham*/
void	draw_line(mlx_image_t *img, t_pixel_data point0, t_pixel_data point1)
{
	t_line_data	line;

	line_limits(&line, point0, point1);
	line_inclined(&line);
	line_straight(&line);
	while (line.x0 != line.x1 || line.y0 != line.y1)
		draw_pixel(img, &line);
}
