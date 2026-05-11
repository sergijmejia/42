/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:02:25 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 18:02:28 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lighting.h"
#include "trace.h"
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846264338327950288
#endif

/**
 * @brief Build orthonormal camera basis (forward, right, up).
 * @param cam Parsed camera (dir must be unit length).
 * @param fwd Output forward (view) axis.
 * @param right Output image horizontal axis.
 * @param up Output image vertical axis.
 * @return None.
 */
static void	cam_axes(t_rt_camera *cam, t_vec *fwd, t_vec *right, t_vec *up)
{
	t_vec	wup;

	*fwd = cam->dir;
	wup = vec(0, 1, 0);
	if (fabs(vec_dot(*fwd, wup)) > 0.99)
		wup = vec(0, 0, 1);
	*right = vec_norm(vec_cross(wup, *fwd));
	*up = vec_norm(vec_cross(*fwd, *right));
}

/**
 * @brief Computes the direction of a ray for a specific pixel.
 * @param cam Camera data.
 * @param ax Structure containing fwd, right, and up vectors.
 * @param x Pixel x coordinate.
 * @param y Pixel y coordinate.
 * @return Normalized direction vector.
 */
static t_vec	cam_ray_dir(t_rt_camera *cam, t_cam_axes ax, int x, int y)
{
	double	tan_h;
	double	u;
	double	v;
	t_vec	rd;

	tan_h = tan((double)cam->fov * M_PI / 360.0);
	u = (2.0 * ((double)x + 0.5) / (double)WIN_W - 1.0) * tan_h;
	v = (1.0 - 2.0 * ((double)y + 0.5) / (double)WIN_H) * tan_h
		* (double)WIN_H / (double)WIN_W;
	rd = vec_add(ax.fwd, vec_add(vec_scale(ax.right, u), vec_scale(ax.up, v)));
	return (vec_norm(rd));
}

/**
 * @brief Write one packed 0xRRGGBB pixel into the MLX image buffer.
 * @param data Runtime data with initialized image address and stride.
 * @param x Horizontal pixel index (column).
 * @param y Vertical pixel index (row).
 * @param color Packed RGB color (0xRRGGBB).
 * @return None.
 */
void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	offset = y * data->img.line_len + x * (data->img.bpp / 8);
	dst = data->img.addr + offset;
	*(unsigned int *)dst = (unsigned int)color;
}

/**
 * @brief Renders a single row of pixels.
 * @param d Global data.
 * @param ax Camera axes.
 * @param y The current row index.
 * @return None.
 */
static void	render_line(t_data *d, t_cam_axes ax, int y)
{
	int			x;
	t_vec		rd;
	t_hit_rec	hit;

	x = 0;
	while (x < WIN_W)
	{
		rd = cam_ray_dir(&d->scene.camera, ax, x, y);
		if (trace_closest(&d->scene, d->scene.camera.pos, rd, &hit))
			put_pixel(d, x, y, shade_hit(d, &hit, rd));
		else
			put_pixel(d, x, y, 0x000000);
		x++;
	}
	return ;
}

/**
 * @brief Main render loop that iterates through all pixels.
 * @param d Global data.
 * @return None.
 */
void	render_scene(t_data *d)
{
	t_cam_axes	ax;
	int			y;

	cam_axes(&d->scene.camera, &ax.fwd, &ax.right, &ax.up);
	y = 0;
	while (y < WIN_H)
	{
		render_line(d, ax, y);
		y++;
	}
	return ;
}
