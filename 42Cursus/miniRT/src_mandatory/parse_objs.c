/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:28:09 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:28:12 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
#include "libft.h"

/**
 * @brief Parse and prepend a sphere object.
 * @param t Token array: sp center diameter color.
 * @param s Scene object list.
 * @return 1 on success, 0 on error.
 */
static int	add_sphere(char **t, t_scene *s)
{
	t_object	*o;

	if (split_len(t) != 4)
		return (0);
	o = (t_object *)malloc(sizeof(t_object));
	if (!o)
		return (0);
	o->type = OBJ_SPHERE;
	o->next = s->objects;
	if (!parse_vec(t[1], &o->sp.center))
		return (free(o), 0);
	o->sp.diameter = ft_atod(t[2]);
	if (o->sp.diameter <= 0 || !parse_color(t[3], &o->sp.color))
		return (free(o), 0);
	s->objects = o;
	return (1);
}

/**
 * @brief Parse and prepend a standard (non-checker) plane.
 * @param t Token array: pl point normal color.
 * @param s Scene object list.
 * @return 1 on success, 0 on error.
 */
static int	add_plane(char **t, t_scene *s)
{
	t_object	*o;

	if (split_len(t) != 4)
		return (0);
	o = (t_object *)malloc(sizeof(t_object));
	if (!o)
		return (0);
	o->type = OBJ_PLANE;
	o->next = s->objects;
	if (!parse_vec(t[1], &o->pl.point) || !parse_vec(t[2], &o->pl.normal))
		return (free(o), 0);
	if (vec_len(o->pl.normal) < 1e-9)
		return (free(o), 0);
	o->pl.normal = vec_norm(o->pl.normal);
	if (!parse_color(t[3], &o->pl.color))
		return (free(o), 0);
	o->pl.checker = 0;
	o->pl.ch_scale = 1.0;
	o->pl.ch_alt.r = 0;
	o->pl.ch_alt.g = 0;
	o->pl.ch_alt.b = 0;
	s->objects = o;
	return (1);
}

/**
 * @brief Parse and prepend a finite cylinder.
 * @param t Token array: cy center axis diameter height color.
 * @param s Scene object list.
 * @return 1 on success, 0 on error.
 */
static int	add_cylinder(char **t, t_scene *s)
{
	t_object	*o;

	if (split_len(t) != 6)
		return (0);
	o = (t_object *)malloc(sizeof(t_object));
	if (!o)
		return (0);
	o->type = OBJ_CYLINDER;
	o->next = s->objects;
	if (!parse_vec(t[1], &o->cy.center) || !parse_vec(t[2], &o->cy.axis))
		return (free(o), 0);
	if (vec_len(o->cy.axis) < 1e-9)
		return (free(o), 0);
	o->cy.axis = vec_norm(o->cy.axis);
	o->cy.diameter = ft_atod(t[3]);
	o->cy.height = ft_atod(t[4]);
	if (o->cy.diameter <= 0 || o->cy.height <= 0)
		return (free(o), 0);
	if (!parse_color(t[5], &o->cy.color))
		return (free(o), 0);
	s->objects = o;
	return (1);
}

/**
 * @brief Dispatch one line of tokens to the correct element parser.
 * @param t NULL-terminated token array; t[0] is the identifier.
 * @param s Scene being built.
 * @return 1 on success, 0 on parse error.
 */
int	parse_tokens(char **t, t_scene *s)
{
	int	r;

	if (!t[0])
		return (1);
	if (!ft_strncmp(t[0], "A", 2))
		return (parse_ambient(t, s));
	if (!ft_strncmp(t[0], "C", 2))
		return (parse_camera(t, s));
	if (!ft_strncmp(t[0], "L", 2))
		return (parse_light(t, s));
	if (!ft_strncmp(t[0], "sp", 3))
		return (add_sphere(t, s));
	r = bonus_try_checker_plane(t, s);
	if (r == 0)
		return (0);
	if (r == 1)
		return (1);
	if (!ft_strncmp(t[0], "pl", 3))
		return (add_plane(t, s));
	if (!ft_strncmp(t[0], "cy", 3))
		return (add_cylinder(t, s));
	if (!ft_strncmp(t[0], "co", 3))
		return (bonus_add_cone(t, s));
	return (put_error("Unknown scene element"));
}
