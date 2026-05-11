/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:59:00 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 17:57:30 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>

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

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
}	t_obj_type;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_rt_ambient
{
	double	ratio;
	t_color	color;
}	t_rt_ambient;

typedef struct s_rt_camera
{
	struct s_vec	pos;
	struct s_vec	dir;
	int				fov;
}	t_rt_camera;

typedef struct s_light_node
{
	struct s_vec		pos;
	double				ratio;
	t_color				color;
	struct s_light_node	*next;
}	t_light_node;

typedef struct s_rt_sphere
{
	struct s_vec	center;
	double			diameter;
	t_color			color;
}	t_rt_sphere;

typedef struct s_rt_plane
{
	struct s_vec	point;
	struct s_vec	normal;
	t_color			color;
	int				checker;
	double			ch_scale;
	t_color			ch_alt;
}	t_rt_plane;

typedef struct s_rt_cylinder
{
	struct s_vec	center;
	struct s_vec	axis;
	double			diameter;
	double			height;
	t_color			color;
}	t_rt_cylinder;

typedef struct s_rt_cone
{
	struct s_vec	center;
	struct s_vec	axis;
	double			diameter;
	double			height;
	t_color			color;
}	t_rt_cone;

typedef struct s_object
{
	t_obj_type			type;
	t_rt_sphere			sp;
	t_rt_plane			pl;
	t_rt_cylinder		cy;
	t_rt_cone			cn;
	struct s_object		*next;
}	t_object;

typedef struct s_scene
{
	t_rt_ambient	ambient;
	t_rt_camera		camera;
	t_light_node	*lights;
	t_object		*objects;
	int				has_ambient;
	int				has_camera;
	int				has_light;
}	t_scene;

int		parse_rt_file(const char *path, t_scene *scene);
int		bonus_append_light(char **t, t_scene *s);
int		bonus_add_cone(char **t, t_scene *s);
int		bonus_try_checker_plane(char **t, t_scene *s);

#endif
