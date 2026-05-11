/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_normals_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 20:06:23 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 20:06:25 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "trace.h"
#include <math.h>

#include "cone_bonus.h"

/**
 * @brief Calculates the normal vector for a cylinder at a given point.
 * @param p Hit point on the cylinder's surface.
 * @param cy Cylinder scene data (center, axis, height).
 * @return t_vec The normalized normal vector at point p.
 */
t_vec	get_cylinder_norm(t_vec p, t_rt_cylinder cy)
{
	t_vec	n;
	double	hax;
	double	half_h;

	half_h = cy.height * 0.5;
	hax = vec_dot(vec_sub(p, cy.center), cy.axis);
	if (hax >= half_h - 1e-3)
		n = cy.axis;
	else if (hax <= -half_h + 1e-3)
		n = vec_scale(cy.axis, -1.0);
	else
		n = vec_norm(vec_sub(vec_sub(p, cy.center), vec_scale(cy.axis, hax)));
	return (n);
}

#ifdef BONUS
/**
 * @brief Logic for calculating the normal vector of a cone (Bonus).
 * @param p Hit point on the cone's surface.
 * @param cn Cone scene data.
 * @return t_vec The normalized normal vector at point p.
 */
t_vec	get_cone_norm(t_vec p, t_rt_cone cn)
{
	t_vec	n;
	t_vec	v_apex;
	t_vec	base_c;

	v_apex = vec_sub(cn.center, vec_scale(cn.axis, cn.height * 0.5));
	base_c = vec_add(v_apex, vec_scale(cn.axis, cn.height));
	if (fabs(vec_dot(vec_sub(p, base_c), cn.axis)) < 1e-2)
		n = cn.axis;
	else
		cone_norm_at(p, cn, &n);
	return (n);
}
#endif

/**
 * @brief Identifies the object type and dispatches to the correct normal
 * formula.
 * @param p Hit point on the object's surface.
 * @param o Pointer to the object hit.
 * @return t_vec The calculated and normalized normal vector for the object.
 */
t_vec	get_obj_norm(t_vec p, t_object *o)
{
	if (o->type == OBJ_SPHERE)
		return (vec_norm(vec_sub(p, o->sp.center)));
	if (o->type == OBJ_PLANE)
		return (o->pl.normal);
	if (o->type == OBJ_CYLINDER)
		return (get_cylinder_norm(p, o->cy));
	if (o->type == OBJ_CONE)
		return (get_cone_norm(p, o->cn));
	return ((t_vec){0, 0, 0});
}
