/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:51:17 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:51:19 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

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
