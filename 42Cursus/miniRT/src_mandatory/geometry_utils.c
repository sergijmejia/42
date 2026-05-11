#include <math.h>
#include "minirt.h"

#define T_MIN 1e-6

/**
 * @brief Solves the quadratic equation for ray-sphere intersection.
 * @param q Pointer to the quadratic structure containing coefficients.
 * @return The nearest positive distance t, or -1.0 if no valid hit exists.
 */
static double	solve_sphere_t(t_quad *q)
{
	double	inv_2a;
	double	sqrt_d;

	q->d = q->b * q->b - 4.0 * q->a * q->c;
	if (q->d < 0)
		return (-1.0);
	inv_2a = 1.0 / (2.0 * q->a);
	sqrt_d = sqrt(q->d);
	q->t = (-q->b - sqrt_d) * inv_2a;
	if (q->t <= T_MIN)
		q->t = (-q->b + sqrt_d) * inv_2a;
	if (q->t <= T_MIN)
		return (-1.0);
	return (q->t);
}

/**
 * @brief Compute ray-sphere intersection and return nearest positive hit.
 * @param ro Ray origin in world coordinates.
 * @param rd Ray direction in world coordinates.
 * @param sp Sphere definition with center and diameter.
 * @return Hit struct with hit flag and nearest distance t.
 */
t_hit	hit_sphere_obj(t_vec ro, t_vec rd, t_rt_sphere sp)
{
	t_hit	hit;
	t_vec	oc;
	t_quad	q;
	double	r;

	hit.hit = 0;
	hit.t = 0;
	oc = vec_sub(ro, sp.center);
	r = sp.diameter * 0.5;
	q.a = vec_dot(rd, rd);
	if (q.a < 1e-12)
		return (hit);
	q.b = 2.0 * vec_dot(oc, rd);
	q.c = vec_dot(oc, oc) - r * r;
	if (solve_sphere_t(&q) < 0)
		return (hit);
	hit.hit = 1;
	hit.t = q.t;
	return (hit);
}

/**
 * @brief Compute ray-plane intersection and return hit information.
 * @param ro Ray origin in world coordinates.
 * @param rd Ray direction in world coordinates.
 * @param p0 A known point on the plane.
 * @param n Plane normal vector (non-zero).
 * @return Hit struct with hit flag and distance t.
 */
t_hit	hit_plane(t_vec ro, t_vec rd, t_vec p0, t_vec n)
{
	t_hit	hit;
	t_vec	oc;
	double	denom;
	double	numer;
	double	t;

	hit.hit = 0;
	hit.t = 0;
	denom = vec_dot(rd, n);
	if (fabs(denom) < 1e-9)
		return (hit);
	oc = vec_sub(p0, ro);
	numer = vec_dot(oc, n);
	t = numer / denom;
	if (t <= T_MIN)
		return (hit);
	hit.hit = 1;
	hit.t = t;
	return (hit);
}