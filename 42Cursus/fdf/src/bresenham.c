/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:15:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/03 18:24:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que dibuja con color*/
static void	draw_color(mlx_image_t *img, t_line_data *line, int i)
{
	img->pixels[i] = line->r0 + (line->r1 - line->r0) * line->color_ratio;
	img->pixels[i + 1] = line->g0 + (line->g1 - line->g0) * line->color_ratio;
	img->pixels[i + 2] = line->b0 + (line->b1 - line->b0) * line->color_ratio;
	img->pixels[i + 3] = 255;
	if (line->dx > line->dy)
		line->color_ratio = line->color_ratio + 1.0 / line->dx;
	else
		line->color_ratio = line->color_ratio + 1.0 / line->dy;
}

/*Funcion que dibuja en negro (borra el dibujo actual)*/
static void	draw_black(mlx_image_t *img, int i)
{
	img->pixels[i] = 0;
	img->pixels[i + 1] = 0;
	img->pixels[i + 2] = 0;
	img->pixels[i + 3] = 0;
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
			draw_color(img, line, index);
		else
			draw_black(img, index);
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
