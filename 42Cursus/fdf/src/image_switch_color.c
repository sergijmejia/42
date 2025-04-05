/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_switch_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:38:23 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/04 19:40:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que gestiona el paso de bgr a rgb*/
static void	bgr_to_rgb(t_image_data *image)
{
	int	i;
	int	aux;

	i = 0;
	while (i < image->len)
	{
		aux = image->map[i].r;
		image->map[i].r = image->map[i].b;
		image->map[i].b = aux;
		i++;
	}
	image->rgb = 1;
}

/*Funcion que gestiona el renderizado personal*/
static void	personalized_color(t_image_data *image, int i, float dif)
{
	float	color;

	color = (1.0 * (image->map[i].z - image->min)) / dif;
	if (color == 0.0)
		color_hexa(image, "FF0000", i);
	if (color < (0.5 / 12))
		color_hexa(image, "FF0000", i);
	else if (color < (1.0 / 12))
		color_hexa(image, "E6B175", i);
	else if (color < (1.5 / 12))
		color_hexa(image, "E6B175", i);
	else if (color < (2.0 / 12))
		color_hexa(image, "55D9A6", i);
	else if (color < (2.5 / 12))
		color_hexa(image, "55D9A6", i);
	else if (color < (4.5 / 12))
		color_hexa(image, "305F7E", i);
	else if (color < (6.0 / 12))
		color_hexa(image, "FFFFFF", i);
	else
		color_hexa(image, "FFFFFF", i);
}

/*Funcion que gestiona el cambio de rgb a personalizado*/
static void	rgb_to_personalized(t_image_data *image)
{
	int		i;
	float	dif;

	i = 0;
	dif = 1.0 * (image->max - image->min);
	while (i < image->len)
	{
		personalized_color(image, i, dif);
		i++;
	}
	image->rgb = 2;
}

/*Funcion que gestiona el cambio de personalizado a bgr*/
static void	personalized_to_bgr(t_image_data *image)
{
	int	i;

	i = 0;
	while (i < image->len)
	{
		image->map[i].r = image->map[i].r0;
		image->map[i].g = image->map[i].g0;
		image->map[i].b = image->map[i].b0;
		i++;
	}
	image->rgb = 0;
}

/*Funcion para el cambio de colores del mapa*/
void	ft_color_switch(t_image_data *image)
{
	if (image->rgb == 0)
		bgr_to_rgb(image);
	else if (image->rgb == 1)
		rgb_to_personalized(image);
	else if (image->rgb == 2)
		personalized_to_bgr(image);
}
