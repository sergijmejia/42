/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:15:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/31 12:22:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que recopila los datos de los puntos p1 y p0 y los almacena en la 
estructura s_line_data*/
static void	line_limits(t_line_data *line, t_pixel_data p0, t_pixel_data p1, int iso_pers)
{
	if (!iso_pers)
	{
		line->x0 = (int) round(p0.iso_x);
		line->y0 = (int) round(p0.iso_y);
		line->x1 = (int) round(p1.iso_x);
		line->y1 = (int) round(p1.iso_y);
	}
	else
	{
		line->x0 = (int) round(p0.pers_x);
		line->y0 = (int) round(p0.pers_y);
		line->x1 = (int) round(p1.pers_x);
		line->y1 = (int) round(p1.pers_y);
	}
	line->r0 = p0.r;
	line->g0 = p0.g;
	line->b0 = p0.b;
	line->r1 = p1.r;
	line->g1 = p1.g;
	line->b1 = p1.b;
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
static void	draw_pixel(mlx_image_t *img, t_line_data *line, int clear)
{
	int		index;
	int		index_limit;

	index = (line->y0 * img->width + line->x0) * 4;
	index_limit = (int)(img->width * img->height * 4);
	if (index >= 0 && index < index_limit && line->x0 > 0 && line->x0 < WIDTH)
	{
		if (!clear)
		{
			img->pixels[index] = line->r0 + (line->r1 - line->r0) * line->color_ratio;
			img->pixels[index + 1] = line->g0 + (line->g1 - line->g0) * line->color_ratio;
			img->pixels[index + 2] = line->b0 + (line->b1 - line->b0) * line->color_ratio;
			img->pixels[index + 3] = 255;
			if (line->dx > line->dy)
				line->color_ratio = line->color_ratio + 1.0 / line->dx;
			else
				line->color_ratio = line->color_ratio + 1.0 / line->dy;
		}
		else
		{
			img->pixels[index] = 0;
			img->pixels[index + 1] = 0;
			img->pixels[index + 2] = 0;
			img->pixels[index + 3] = 0;
		}
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
void	draw_line(t_image_data *img, t_pixel_data p0, t_pixel_data p1, int clr)
{
	t_line_data	line;

	line_limits(&line, p0, p1, img->iso_pers);
	line_inclined(&line);
	line_straight(&line);
	line.color_ratio = 0.0;
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		if (img->iso_pers == 0)
			draw_pixel(img->img_iso, &line, clr);
		else
			draw_pixel(img->img_pers, &line, clr);
	}
}
