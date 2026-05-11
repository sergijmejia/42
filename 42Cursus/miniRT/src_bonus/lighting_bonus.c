/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:59:59 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 18:00:02 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lighting.h"
#include "trace.h"
#include <math.h>

# define SHADOW_BIAS 1e-4
# define SPEC_POW 32.0



/**
 * @brief Calculates and initializes the RGB array with the ambient light component.
 * @param d Pointer to the global data structure.
 * @param rec The hit record containing surface information (point, normal, color).
 * @param rgb Array of 3 doubles to store the resulting red, green, and blue components.
 * @return None.
 */
static void	init_ambient_color(t_data *d, t_hit_rec *rec, double rgb[3])
{
	t_color	obj;
	t_color	amb;

	obj = checker_color(rec);
	amb = d->scene.ambient.color;
	rgb[0] = (double)obj.r * d->scene.ambient.ratio * (double)amb.r / 255.0;
	rgb[1] = (double)obj.g * d->scene.ambient.ratio * (double)amb.g / 255.0;
	rgb[2] = (double)obj.b * d->scene.ambient.ratio * (double)amb.b / 255.0;
}

/**
 * @brief Computes the specular light component using the Blinn-Phong model.
 * @param n Surface normal vector at the hit point.
 * @param l Normalized vector pointing from the hit point to the light source.
 * @param v Normalized vector pointing from the hit point to the camera (view).
 * @return double The intensity of the specular reflection.
 */
static double	get_specular(t_vec n, t_vec l, t_vec v)
{
	t_vec	refl;
	double	spec;
	double	ndotl;

	ndotl = vec_dot(n, l);
	if (ndotl <= 0)
		return (0.0);
	refl = vec_sub(vec_scale(n, 2.0 * ndotl), l);
	spec = vec_dot(v, vec_norm(refl));
	if (spec < 0)
		return (0.0);
	return (pow(spec, SPEC_POW));
}

/**
 * @brief Accumulates the diffuse and specular contributions of a light source.
 * @param rec The hit record of the intersected object.
 * @param ln Pointer to the current light node being processed.
 * @param rgb Array of 3 doubles where color accumulation is stored.
 * @param ds Array containing calculated [0] diffuse and [1] specular intensities.
 * @return None.
 */
static void	add_light_contrib(t_hit_rec *rec, t_light_node *ln,
		double rgb[3], double ds[2])
{
	t_color	obj;

	obj = checker_color(rec);
	rgb[0] += (double)obj.r * ln->ratio * ds[0] * (double)ln->color.r / 255.0;
	rgb[1] += (double)obj.g * ln->ratio * ds[0] * (double)ln->color.g / 255.0;
	rgb[2] += (double)obj.b * ln->ratio * ds[0] * (double)ln->color.b / 255.0;
	rgb[0] += (double)ln->color.r * ln->ratio * ds[1];
	rgb[1] += (double)ln->color.g * ln->ratio * ds[1];
	rgb[2] += (double)ln->color.b * ln->ratio * ds[1];
}

/**
 * @brief Determines if a point on a surface is directly lit by a light source.
 * @param scene Pointer to the scene structure for intersection testing.
 * @param p The point on the surface to check.
 * @param n The surface normal (used for biasing the shadow ray).
 * @param ln The light source to check against.
 * @return int 1 if the point is lit, 0 if it is in shadow.
 */
static int	is_lit(t_scene *scene, t_vec p, t_vec n, t_light_node *ln)
{
	t_ray		s_ray;
	t_hit_rec	sh;
	t_vec		l_vec;
	double		dist;

	l_vec = vec_sub(ln->pos, p);
	dist = vec_len(l_vec);
	s_ray.d = vec_scale(l_vec, 1.0 / dist);
	s_ray.o = vec_add(p, vec_scale(n, SHADOW_BIAS));
	if (trace_closest_skip(scene, s_ray, &sh, NULL))
	{
		if (sh.hit && sh.t < dist - SHADOW_BIAS)
			return (0);
	}
	return (1);
}

/**
 * @brief Phong shading with shadows, colored lights, and checker planes (bonus).
 * @param d Runtime data with scene and lights.
 * @param rec Closest hit data for shading.
 * @param rd Primary ray direction (unit) toward the camera.
 * @return Packed RGB pixel value.
 */
int	shade_hit(t_data *d, t_hit_rec *rec, t_vec rd)
{
	t_light_node	*ln;
	double			rgb[3];
	double			ds[2];

	init_ambient_color(d, rec, rgb);
	ln = d->scene.lights;
	while (ln)
	{
		if (is_lit(&d->scene, rec->p, rec->n, ln))
		{
			ds[0] = fmax(0.0, vec_dot(rec->n, vec_norm(vec_sub(ln->pos, rec->p))));
			ds[1] = get_specular(rec->n, vec_norm(vec_sub(ln->pos, rec->p)),
					vec_scale(rd, -1.0));
			add_light_contrib(rec, ln, rgb, ds);
		}
		ln = ln->next;
	}
	return (pack_rgb(rgb[0], rgb[1], rgb[2]));
}