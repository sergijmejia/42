#include "minirt.h"
#include <math.h>

# define T_MIN 1e-6

/**
 * @brief Compute cone apex from midpoint center and axis.
 * @param cn Cone with center at midpoint of axis segment.
 * @return Position of the apex point.
 */
t_vec	cone_apex(t_rt_cone cn)
{
	return (vec_sub(cn.center, vec_scale(cn.axis, cn.height * 0.5)));
}

/**
 * @brief Checks if the intersection point is within the cone's height limits.
 * @param ro Ray origin.
 * @param rd Ray direction.
 * @param cn Cone scene data.
 * @param t Distance to the intersection point.
 * @return int 1 if the point is within the cone's height, 0 otherwise.
 */
int	is_valid_u(t_vec ro, t_vec rd, t_rt_cone cn, double t)
{
	t_vec	p;
	double	u;

	if (t <= T_MIN)
		return (0);
	p = vec_add(ro, vec_scale(rd, t));
	u = vec_dot(vec_sub(p, cone_apex(cn)), cn.axis);
	return (u >= -1e-7 && u <= cn.height + 1e-7);
}

/**
 * @brief Outward geometric normal on cone side at point p (not on cap).
 * @param p Surface point on the cone side.
 * @param cn Cone definition.
 * @param n Output unit normal vector.
 * @return None.
 */
void	cone_norm_at(t_vec p, t_rt_cone cn, t_vec *n)
{
	t_vec	w;
	t_vec	g;
	double	k;
	double	h;
	double	r;

	h = cn.height;
	r = cn.diameter * 0.5;
	w = vec_sub(p, cone_apex(cn));
	k = (h * h) / (h * h + r * r);
	g = vec_sub(vec_scale(cn.axis, vec_dot(w, cn.axis)), vec_scale(w, k));
	*n = vec_norm(g);
	if (vec_len(*n) < 1e-9)
		*n = cn.axis;
}