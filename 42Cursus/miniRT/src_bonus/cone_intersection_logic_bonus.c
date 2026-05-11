#include "minirt.h"
#include "cone_bonus.h"
#include <math.h>

/**
 * @brief Sets up and solves the quadratic equation for ray-cone intersection.
 * @param ro Ray origin.
 * @param rd Ray direction.
 * @param cn Cone scene data.
 * @param q Pointer to quadratic structure to store coefficients and discriminant.
 * @return int 1 if the discriminant is non-negative and 'a' is non-zero, 0 otherwise.
 */
static int	solve_side_quad(t_vec ro, t_vec rd, t_rt_cone cn, t_quad *q)
{
	t_vec	oc;
	double	k;
	double	dot[3];

	oc = vec_sub(ro, cone_apex(cn));
	k = (cn.height * cn.height) / (cn.height * cn.height 
			+ (cn.diameter * 0.5) * (cn.diameter * 0.5));
	dot[0] = vec_dot(rd, cn.axis);
	dot[1] = vec_dot(oc, cn.axis);
	dot[2] = vec_dot(oc, rd);
	q->a = dot[0] * dot[0] - k * vec_dot(rd, rd);
	q->b = 2.0 * (dot[1] * dot[0] - k * dot[2]);
	q->c = dot[1] * dot[1] - k * vec_dot(oc, oc);
	q->d = q->b * q->b - 4.0 * q->a * q->c;
	return (q->d >= 0 && fabs(q->a) > 1e-12);
}

/**
 * @brief Calculates the intersection distance with the side surface of a cone.
 * @param ro Ray origin.
 * @param rd Ray direction.
 * @param cn Cone scene data.
 * @param out_t Pointer to store the resulting distance.
 * @return int 1 if a valid intersection is found, 0 otherwise.
 */
int	hit_cone_side(t_vec ro, t_vec rd, t_rt_cone cn, double *out_t)
{
	t_quad	q;
	double	t1;
	double	t2;
	int		v1;
	int		v2;

	if (!solve_side_quad(ro, rd, cn, &q))
		return (0);
	q.d = sqrt(q.d);
	t1 = (-q.b - q.d) / (2.0 * q.a);
	t2 = (-q.b + q.d) / (2.0 * q.a);
	v1 = is_valid_u(ro, rd, cn, t1);
	v2 = is_valid_u(ro, rd, cn, t2);
	if (v1 && v2)
	{
		if (t1 < t2)
			*out_t = t1;
		else
			*out_t = t2;
		return (1);
	}
	if (v1)
		return (*out_t = t1, 1);
	if (v2)
		return (*out_t = t2, 1);
	return (0);
}