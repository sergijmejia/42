/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:01:47 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 18:01:50 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lighting.h"
#include "trace.h"
#include <math.h>

# define SHADOW_BIAS 1e-4

/**
 * @brief Calculates ambient light component for the hit object.
 * @param d Global data.
 * @param obj Object color.
 * @return t_vec containing the initial RGB ambient contribution.
 */
static t_vec	calc_ambient(t_data *d, t_color obj)
{
	t_vec	amb_rgb;
	t_color	amb;
	double	ratio;

	amb = d->scene.ambient.color;
	ratio = d->scene.ambient.ratio;
	amb_rgb.x = (double)obj.r * ratio * (double)amb.r / 255.0;
	amb_rgb.y = (double)obj.g * ratio * (double)amb.g / 255.0;
	amb_rgb.z = (double)obj.b * ratio * (double)amb.b / 255.0;
	return (amb_rgb);
}

/**
 * @brief Checks if a point is in shadow relative to a light source.
 * @param d Global data.
 * @param rec Hit record of the object.
 * @param l Normalized vector to light.
 * @param dist Distance to light source.
 * @return int 1 if in shadow, 0 otherwise.
 */
static int	is_in_shadow(t_data *d, t_hit_rec *rec, t_vec l, double dist)
{
	t_hit_rec	sh;
	t_ray		shadow_ray;

	shadow_ray.o = vec_add(rec->p, vec_scale(rec->n, SHADOW_BIAS));
	shadow_ray.d = l;
	if (trace_closest_skip(&d->scene, shadow_ray, &sh, rec->obj)
		&& sh.hit && sh.t > SHADOW_BIAS
		&& sh.t < dist - SHADOW_BIAS)
		return (1);
	return (0);
}

/**
 * @brief Computes diffuse lighting for all light sources in the scene.
 * @param d Global data.
 * @param rec Hit record.
 * @param rgb Pointer to the accumulated RGB vector.
 * @return None.
 */
static void	apply_lights(t_data *d, t_hit_rec *rec, t_vec *rgb)
{
	t_light_node	*ln;
	t_vec			l;
	double			dist;
	double			diff;

	ln = d->scene.lights;
	while (ln)
	{
		l = vec_sub(ln->pos, rec->p);
		dist = sqrt(vec_dot(l, l));
		if (dist > 1e-6)
		{
			l = vec_scale(l, 1.0 / dist);
			diff = vec_dot(rec->n, l);
			if (diff > 0 && !is_in_shadow(d, rec, l, dist))
			{
				rgb->x += (double)rec->color.r * ln->ratio * diff;
				rgb->y += (double)rec->color.g * ln->ratio * diff;
				rgb->z += (double)rec->color.b * ln->ratio * diff;
			}
		}
		ln = ln->next;
	}
	return ;
}

/**
 * @brief Final shade_hit function that combines ambient and diffuse lighting.
 * @param d Global data.
 * @param rec Hit record.
 * @param rd Ray direction (unused).
 * @return int Packed RGB color.
 */
int	shade_hit(t_data *d, t_hit_rec *rec, t_vec rd)
{
	t_vec	rgb;

	(void)rd;
	rgb = calc_ambient(d, rec->color);
	apply_lights(d, rec, &rgb);
	return (pack_rgb(rgb.x, rgb.y, rgb.z));
}