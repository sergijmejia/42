/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:20:00 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 18:01:23 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

#define T_MIN 1e-6

/**
 * @brief Checks if the intersection point on the infinite cylinder side 
 * falls within the cylinder's height.
 * @param t Distance from ray origin to the intersection.
 * @param ro Ray origin.
 * @param rd Ray direction.
 * @param d Pointer to the cylinder data structure.
 * @return None.
 */
static void	try_cyl_t(double t, t_vec ro, t_vec rd, t_cyl_data *d)
{
	t_vec	p;
	double	h;

	if (t <= T_MIN)
		return ;
	p = vec_add(ro, vec_scale(rd, t));
	h = vec_dot(vec_sub(p, vec_sub(ro, d->oc)), d->a);
	if (fabs(h) > d->h_h + 1e-7)
		return ;
	if (t < d->best_t)
	{
		d->best_t = t;
		d->found = 1;
	}
	return ;
}

/**
 * @brief Checks if an intersection point on a cap's plane falls within its
 * radius.
 * @param t Distance from ray origin to the plane intersection.
 * @param cap_c Center point of the specific cap being tested.
 * @param c Pointer to the auxiliary cap data (ray and radius info).
 * @param d Pointer to the cylinder data for updating best hit results.
 * @return None.
 */
static void	try_cap(double t, t_vec cap_c, t_cap_data *c, t_cyl_data *d)
{
	t_vec	p;
	t_vec	rad;
	double	d2;

	if (t <= T_MIN)
		return ;
	p = vec_add(c->ro, vec_scale(c->rd, t));
	rad = vec_sub(p, cap_c);
	d2 = vec_dot(rad, rad);
	if (d2 > c->r2 + 1e-7)
		return ;
	if (t < d->best_t)
	{
		d->best_t = t;
		d->found = 1;
	}
}

/**
 * @brief Computes the quadratic equation for the cylinder side and tests hits.
 * @param ro Ray origin.
 * @param rd Ray direction.
 * @param cy Cylinder scene data (unused in this version).
 * @param d Pointer to the main cylinder data structure.
 * @return None.
 */
static void	check_side(t_vec ro, t_vec rd, t_rt_cylinder cy, t_cyl_data *d)
{
	t_quad	q;
	t_vec	dv;
	t_vec	fv;
	double	sqrt_d;

	(void)cy;
	dv = vec_sub(rd, vec_scale(d->a, vec_dot(rd, d->a)));
	fv = vec_sub(d->oc, vec_scale(d->a, vec_dot(d->oc, d->a)));
	q.a = vec_dot(dv, dv);
	if (q.a <= 1e-12)
		return ;
	q.b = 2.0 * vec_dot(fv, dv);
	q.c = vec_dot(fv, fv) - d->r2;
	q.d = q.b * q.b - 4.0 * q.a * q.c;
	if (q.d < 0)
		return ;
	sqrt_d = sqrt(q.d);
	try_cyl_t((-q.b - sqrt_d) / (2.0 * q.a), ro, rd, d);
	try_cyl_t((-q.b + sqrt_d) / (2.0 * q.a), ro, rd, d);
	return ;
}

/**
 * @brief Calculates and tests intersections for both top and bottom caps.
 * @param ro Ray origin in world coordinates.
 * @param rd Ray direction in world coordinates.
 * @param cy Cylinder scene data (center and height).
 * @param d Pointer to the main cylinder data structure.
 * @return None.
 */
static void	check_caps(t_vec ro, t_vec rd, t_rt_cylinder cy, t_cyl_data *d)
{
	double		denom;
	double		t;
	t_cap_data	c_d;

	c_d.ro = ro;
	c_d.rd = rd;
	c_d.r2 = d->r2;
	denom = vec_dot(rd, d->a);
	if (fabs(denom) <= 1e-9)
		return ;
	t = (d->h_h - vec_dot(d->oc, d->a)) / denom;
	try_cap(t, vec_add(cy.center, vec_scale(d->a, d->h_h)), &c_d, d);
	t = (-d->h_h - vec_dot(d->oc, d->a)) / denom;
	try_cap(t, vec_add(cy.center, vec_scale(d->a, -d->h_h)), &c_d, d);
}

/**
 * @brief Finite cylinder: side + caps; axis and normals from scene data.
 * @param ro Ray origin in world coordinates.
 * @param rd Ray direction in world coordinates.
 * @param cy Cylinder definition (center, axis, diameter, height).
 * @return Hit struct with the nearest intersection point found.
 */
t_hit	hit_cylinder_obj(t_vec ro, t_vec rd, t_rt_cylinder cy)
{
	t_hit		hit;
	t_cyl_data	d;

	hit.hit = 0;
	hit.t = 0;
	d.a = vec_norm(cy.axis);
	if (vec_len(d.a) < 1e-9)
		return (hit);
	d.r2 = (cy.diameter * 0.5) * (cy.diameter * 0.5);
	d.h_h = cy.height * 0.5;
	d.oc = vec_sub(ro, cy.center);
	d.best_t = 1e30;
	d.found = 0;
	check_side(ro, rd, cy, &d);
	check_caps(ro, rd, cy, &d);
	if (d.found)
	{
		hit.hit = 1;
		hit.t = d.best_t;
	}
	return (hit);
}
