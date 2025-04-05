/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:47:40 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/03 17:52:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que recopila los datos de los puntos p1 y p0 y los almacena en la 
estructura s_line_data*/
void	line_limits(t_line_data *ln, t_pixel_data p0, t_pixel_data p1, int i_p)
{
	if (!i_p)
	{
		ln->x0 = (int) round(p0.iso_x);
		ln->y0 = (int) round(p0.iso_y);
		ln->x1 = (int) round(p1.iso_x);
		ln->y1 = (int) round(p1.iso_y);
	}
	else
	{
		ln->x0 = (int) round(p0.pers_x);
		ln->y0 = (int) round(p0.pers_y);
		ln->x1 = (int) round(p1.pers_x);
		ln->y1 = (int) round(p1.pers_y);
	}
	ln->r0 = p0.r;
	ln->g0 = p0.g;
	ln->b0 = p0.b;
	ln->r1 = p1.r;
	ln->g1 = p1.g;
	ln->b1 = p1.b;
	ln->dx = ln->x1 - ln->x0;
	ln->dy = ln->y1 - ln->y0;
}

/*Funcion que recopila los datos de los avances inclinados y los almacena en
la estructura s_line_data*/
void	line_inclined(t_line_data *line)
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
void	line_straight(t_line_data *line)
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
