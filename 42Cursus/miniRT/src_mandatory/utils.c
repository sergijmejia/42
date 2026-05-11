/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:20:00 by rafaguti          #+#    #+#             */
/*   Updated: 2026/04/29 21:05:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief Build and return a 3D vector from three coordinates.
 * @param x X coordinate value.
 * @param y Y coordinate value.
 * @param z Z coordinate value.
 * @return Initialized vector value.
 */
t_vec vec(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/**
 * @brief Add two 3D vectors component-wise.
 * @param a First vector operand.
 * @param b Second vector operand.
 * @return Sum vector.
 */
t_vec	vec_add(t_vec a, t_vec b)
{
	return (vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

/**
 * @brief Subtract vector b from vector a.
 * @param a First vector operand.
 * @param b Second vector operand.
 * @return Difference vector.
 */
t_vec	vec_sub(t_vec a, t_vec b)
{
	return (vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

/**
 * @brief Multiply a 3D vector by a scalar value.
 * @param v Vector to scale.
 * @param s Scalar multiplier.
 * @return Scaled vector.
 */
t_vec	vec_scale(t_vec v, double s)
{
	return (vec(v.x * s, v.y * s, v.z * s));
}

/**
 * @brief Compute dot product between two vectors.
 * @param a First vector operand.
 * @param b Second vector operand.
 * @return Scalar dot product result.
 */
double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief Compute cross product a x b.
 * @param a First vector.
 * @param b Second vector.
 * @return Cross product vector.
 */
t_vec	vec_cross(t_vec a, t_vec b)
{
	return (vec(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

/**
 * @brief Compute Euclidean length of a vector.
 * @param v Input vector.
 * @return Vector magnitude.
 */
double	vec_len(t_vec v)
{
	return (sqrt(vec_dot(v, v)));
}

/**
 * @brief Return normalized vector or zero when length is tiny.
 * @param v Input vector.
 * @return Unit vector in same direction.
 */
t_vec	vec_norm(t_vec v)
{
	double	len;

	len = vec_len(v);
	if (len < 1e-9)
		return (vec(0, 0, 0));
	return (vec_scale(v, 1.0 / len));
}

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
