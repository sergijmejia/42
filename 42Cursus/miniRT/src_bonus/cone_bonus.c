/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:59:42 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 17:59:48 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "cone_bonus.h"
#include <math.h>

# define T_MIN 1e-6

/**
 * @brief Checks intersection with the cone's circular base.
 * @param t Distance to the plane of the base.
 * @param ray The ray (origin and direction).
 * @param base_c Center point of the base.
 * @param ch Pointer to the hit result structure.
 * @return None.
 */
static void	try_cone_cap(double t, t_ray ray, t_vec base_c, t_cone_hit *ch)
{
	t_vec	p;
	t_vec	rad;

	if (t <= T_MIN)
		return ;
	p = vec_add(ray.o, vec_scale(ray.d, t));
	rad = vec_sub(p, base_c);
	if (vec_dot(rad, rad) > ch->r2 + 1e-7)
		return ;
	if (t < ch->best_t)
	{
		ch->best_t = t;
		ch->found = 1;
	}
}

/**
 * @brief Logic to check cone cap and side intersections.
 * @param ray The ray (origin and direction).
 * @param cn Cone data.
 * @param ch Pointer to hit result structure.
 * @return None.
 */
static void	check_cone_parts(t_ray ray, t_rt_cone cn, t_cone_hit *ch)
{
	t_vec	base_c;
	double	denom;
	double	t_side;

	base_c = vec_add(cone_apex(cn), vec_scale(cn.axis, cn.height));
	denom = vec_dot(ray.d, cn.axis);
	if (fabs(denom) > 1e-9)
		try_cone_cap(vec_dot(vec_sub(base_c, ray.o), cn.axis) / denom,
			ray, base_c, ch);
	if (hit_cone_side(ray.o, ray.d, cn, &t_side) && t_side < ch->best_t)
	{
		ch->best_t = t_side;
		ch->found = 1;
	}
}

/**
 * @brief Main function to detect hit on a cone object.
 * @param ro Ray origin.
 * @param rd Ray direction.
 * @param cn Cone structure.
 * @return t_hit Hit record structure.
 */
t_hit	hit_cone_obj(t_vec ro, t_vec rd, t_rt_cone cn)
{
	t_hit		h;
	t_ray		ray;
	t_cone_hit	ch;

	h.hit = 0;
	h.t = 0;
	ray.o = ro;
	ray.d = rd;
	ch.best_t = 1e30;
	ch.found = 0;
	ch.r2 = (cn.diameter * 0.5) * (cn.diameter * 0.5);
	check_cone_parts(ray, cn, &ch);
	if (!ch.found)
		return (h);
	h.hit = 1;
	h.t = ch.best_t;
	return (h);
}