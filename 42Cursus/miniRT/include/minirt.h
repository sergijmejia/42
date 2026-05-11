/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:20:00 by rafaguti          #+#    #+#             */
/*   Updated: 2026/04/29 21:05:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdlib.h>

# define WIN_W 800
# define WIN_H 600

typedef struct s_hit
{
	double	t;
	int		hit;
}	t_hit;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_quad
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;
}	t_quad;

typedef struct s_cyl_data
{
	t_vec	a;
	t_vec	oc;
	double	r2;
	double	h_h;
	double	best_t;
	int		found;
}	t_cyl_data;

typedef struct s_cap_data
{
	t_vec	ro;
	t_vec	rd;
	double	r2;
}	t_cap_data;

# include "parser.h"

typedef struct s_hit_rec
{
	double		t;
	int		hit;
	t_vec		p;
	t_vec		n;
	t_color		color;
	t_object	*obj;
}	t_hit_rec;

typedef struct s_cam
{
	double	x;
	double	y;
	double	z;
}	t_cam;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_cam	cam;
	t_scene	scene;
}	t_data;

typedef struct s_cam_axes
{
	t_vec	fwd;
	t_vec	right;
	t_vec	up;
}	t_cam_axes;

typedef struct s_ray
{
	t_vec	o;
	t_vec	d;
}	t_ray;

typedef struct s_cone_hit
{
	double	best_t;
	int		found;
	double	r2;
}	t_cone_hit;

/* init */
void	init_mlx(t_data *data);
void	init_window(t_data *data);
void	init_image(t_data *data);

/* render */
void	render_scene(t_data *data);
void	present_image(t_data *data);
void	put_pixel(t_data *data, int x, int y, int color);

/* geometry */
t_hit	hit_sphere_obj(t_vec ro, t_vec rd, t_rt_sphere sp);
t_hit	hit_plane(t_vec ro, t_vec rd, t_vec p0, t_vec n);
t_hit	hit_cylinder_obj(t_vec ro, t_vec rd, t_rt_cylinder cy);

/* hooks */
void	init_hooks(t_data *data);
int	key_press(int keycode, void *param);
int	close_window(void *param);
int	expose_redraw(void *param);
int		cleanup_and_exit(t_data *data, int exit_code);
void	scene_objects_clear(t_scene *scene);
void	scene_lights_clear(t_scene *scene);

/* parse */
int		put_error(char *msg);
int		is_space(char c);
int		split_len(char **split);
void	free_split(char **split);
double	ft_atod(const char *str);
int		parse_vec(char *str, t_vec *v);
int		parse_color(char *str, t_color *c);
int		has_rt_extension(const char *path);
void	init_scene_struct(t_scene *scene);
int		parse_ambient(char **t, t_scene *s);
int		parse_camera(char **t, t_scene *s);
int		parse_light(char **t, t_scene *s);
int		parse_tokens(char **t, t_scene *s);
char	*read_rt_full(int fd);
int		parse_error_cleanup(t_scene *scene);

/* trace */
t_vec	get_cylinder_norm(t_vec p, t_rt_cylinder cy);
t_vec	get_cylinder_norm(t_vec p, t_rt_cylinder cy);
t_vec	get_obj_norm(t_vec p, t_object *o);

/* utils */
t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_scale(t_vec v, double s);
double	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
double	vec_len(t_vec v);
t_vec	vec_norm(t_vec v);
int		rgb_to_int(t_color color, double intensity);
int     pack_rgb(double r, double g, double b);

#endif
