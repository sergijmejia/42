/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:51:09 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:51:11 by smejia-a         ###   ########.fr       */
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
t_vec	vec(double x, double y, double z)
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
