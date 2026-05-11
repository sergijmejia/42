/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:51:34 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:51:36 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief Clamp one color channel to [0, 255].
 * @param value Channel integer value.
 * @return Clamped channel value.
 */
static int	clamp_channel(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

/**
 * @brief Clamp a floating channel to integer 0-255.
 * @param v Input intensity.
 * @return Nearest valid channel value.
 */
static int	clamp_channel_d(double v)
{
	if (v < 0.0)
		return (0);
	if (v > 255.0)
		return (255);
	return ((int)v);
}

/**
 * @brief Convert color and light intensity into packed RGB integer.
 * @param color Base RGB color channels.
 * @param intensity Light intensity multiplier.
 * @return Packed 0xRRGGBB integer color.
 */
int	rgb_to_int(t_color color, double intensity)
{
	int	r;
	int	g;
	int	b;

	r = clamp_channel((int)(color.r * intensity));
	g = clamp_channel((int)(color.g * intensity));
	b = clamp_channel((int)(color.b * intensity));
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Pack three clamped channels into a 0xRRGGBB integer.
 * @param r Red channel (double).
 * @param g Green channel (double).
 * @param b Blue channel (double).
 * @return Packed pixel color.
 */
int	pack_rgb(double r, double g, double b)
{
	return ((clamp_channel_d(r) << 16) | (clamp_channel_d(g) << 8)
		| clamp_channel_d(b));
}
