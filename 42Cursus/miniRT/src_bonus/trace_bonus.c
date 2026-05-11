/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 20:03:18 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 20:03:21 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "trace.h"
#include <math.h>

#include "cone_bonus.h"

/**
 * @brief Fills basic hit record data common to all objects.
 * @param rec Pointer to the hit record to be filled.
 * @param o Pointer to the object that was hit.
 * @param t Distance from the ray origin to the hit point.
 * @param p The exact coordinates of the hit point in world space.
 * @return None.
 */
static void	fill_rec(t_hit_rec *rec, t_object *o, double t, t_vec p)
{
	rec->t = t;
	rec->p = p;
	rec->obj = o;
	rec->hit = 1;
	if (o->type == OBJ_SPHERE)
		rec->color = o->sp.color;
	else if (o->type == OBJ_PLANE)
		rec->color = o->pl.color;
	else if (o->type == OBJ_CYLINDER)
		rec->color = o->cy.color;
	else if (o->type == OBJ_CONE)
		rec->color = o->cn.color;
}

/**
 * @brief Fill hit record for one object if the ray hits it.
 * @param o Object pointer.
 * @param ro Ray origin.
 * @param rd Ray direction (unit).
 * @param rec Output hit data.
 * @return 1 if hit, 0 otherwise.
 */
int	trace_object_hit(t_object *o, t_vec ro, t_vec rd, t_hit_rec *rec)
{
	t_hit	h;
	t_vec	n;

	h.hit = 0;
	if (o->type == OBJ_SPHERE)
		h = hit_sphere_obj(ro, rd, o->sp);
	else if (o->type == OBJ_PLANE)
		h = hit_plane(ro, rd, o->pl.point, o->pl.normal);
	else if (o->type == OBJ_CYLINDER)
		h = hit_cylinder_obj(ro, rd, o->cy);
	else if (o->type == OBJ_CONE)
		h = hit_cone_obj(ro, rd, o->cn);
	if (!h.hit)
		return (0);
	fill_rec(rec, o, h.t, vec_add(ro, vec_scale(rd, h.t)));
	n = get_obj_norm(rec->p, o);
	if (vec_dot(n, rd) > 0)
		n = vec_scale(n, -1.0);
	rec->n = n;
	return (1);
}

/**
 * @brief Closest hit along ray over all objects, optionally skipping one.
 * @param scene Scene with object list.
 * @param ray Structure containing origin and direction.
 * @param out Closest hit record.
 * @param skip Object ignored (to avoid self-intersection).
 * @return int 1 if something was hit, 0 otherwise.
 */
int	trace_closest_skip(t_scene *scene, t_ray ray, t_hit_rec *out,
	t_object *skip)
{
	t_object	*obj;
	t_hit_rec	rec;
	int			any;

	obj = scene->objects;
	any = 0;
	out->t = 1e30;
	while (obj)
	{
		if (obj != skip && trace_object_hit(obj, ray.o, ray.d, &rec))
		{
			if (rec.hit && rec.t < out->t)
			{
				*out = rec;
				any = 1;
			}
		}
		obj = obj->next;
	}
	return (any);
}

/**
 * @brief Closest hit along ray over all objects.
 * @param scene Scene with object list.
 * @param ro Ray origin.
 * @param rd Ray direction.
 * @param out Closest hit record.
 * @return int 1 if something was hit, 0 otherwise.
 */
int	trace_closest(t_scene *scene, t_vec ro, t_vec rd, t_hit_rec *out)
{
	t_ray	ray;

	ray.o = ro;
	ray.d = rd;
	return (trace_closest_skip(scene, ray, out, NULL));
}
