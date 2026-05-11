/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:00:11 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 18:00:15 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "parser_bonus.h"
#include "libft.h"

/**
 * @brief Parse RGB color with range check.
 * @param str Comma-separated r,g,b.
 * @param c Output color.
 * @return 1 on success, 0 on failure.
 */
static int	bonus_parse_color(char *str, t_color *c)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || split_len(rgb) != 3)
		return (free_split(rgb), 0);
	c->r = ft_atoi(rgb[0]);
	c->g = ft_atoi(rgb[1]);
	c->b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (c->r < 0 || c->r > 255 || c->g < 0 || c->g > 255
		|| c->b < 0 || c->b > 255)
		return (0);
	return (1);
}

/**
 * @brief Append another point light (bonus multi-light).
 * @param t Token line: L position ratio optional_color.
 * @param s Scene receiving the new head of lights list.
 * @return 1 on success, 0 on error.
 */
int	bonus_append_light(char **t, t_scene *s)
{
	t_light_node	*node;

	if (split_len(t) < 3 || split_len(t) > 4)
		return (0);
	node = malloc(sizeof(*node));
	if (!node)
		return (0);
	if (!bonus_parse_vec(t[1], &node->pos))
		return (free(node), 0);
	node->ratio = bonus_atod(t[2]);
	if (node->ratio < 0.0 || node->ratio > 1.0)
		return (free(node), 0);
	if (split_len(t) == 4 && !bonus_parse_color(t[3], &node->color))
		return (free(node), 0);
	if (split_len(t) == 3)
	{
		node->color.r = 255;
		node->color.g = 255;
		node->color.b = 255;
	}
	node->next = s->lights;
	s->lights = node;
	return (1);
}

/**
 * @brief Parse finite cone: co center axis diameter height color.
 * @param t Token line for cone.
 * @param s Scene object list.
 * @return 1 on success, 0 on error.
 */
int	bonus_add_cone(char **t, t_scene *s)
{
	t_object	*o;

	if (split_len(t) != 6)
		return (0);
	o = malloc(sizeof(*o));
	if (!o)
		return (0);
	o->type = OBJ_CONE;
	o->next = s->objects;
	if (!bonus_parse_vec(t[1], &o->cn.center) || !bonus_parse_vec(t[2], &o->cn.axis))
		return (free(o), 0);
	if (vec_len(o->cn.axis) < 1e-9)
		return (free(o), 0);
	o->cn.axis = vec_norm(o->cn.axis);
	o->cn.diameter = bonus_atod(t[3]);
	o->cn.height = bonus_atod(t[4]);
	if (o->cn.diameter <= 0 || o->cn.height <= 0)
		return (free(o), 0);
	if (!bonus_parse_color(t[5], &o->cn.color))
		return (free(o), 0);
	s->objects = o;
	return (1);
}

/**
 * @brief Parse checker plane: pl point normal chk scale c1 c2.
 * @param t Token line starting with pl.
 * @param s Scene object list.
 * @return 1 if parsed, 0 on error, -1 if not a checker plane line.
 */
int	bonus_try_checker_plane(char **t, t_scene *s)
{
	t_object	*o;

	if (ft_strncmp(t[0], "pl", 3) || split_len(t) != 7)
		return (-1);
	if (ft_strncmp(t[3], "chk", 4))
		return (-1);
	o = malloc(sizeof(*o));
	if (!o)
		return (0);
	o->type = OBJ_PLANE;
	o->next = s->objects;
	if (!bonus_parse_vec(t[1], &o->pl.point) || !bonus_parse_vec(t[2], &o->pl.normal))
		return (free(o), 0);
	if (vec_len(o->pl.normal) < 1e-9)
		return (free(o), 0);
	o->pl.normal = vec_norm(o->pl.normal);
	o->pl.ch_scale = bonus_atod(t[4]);
	if (o->pl.ch_scale <= 0)
		return (free(o), 0);
	if (!bonus_parse_color(t[5], &o->pl.color)
		|| !bonus_parse_color(t[6], &o->pl.ch_alt))
		return (free(o), 0);
	o->pl.checker = 1;
	s->objects = o;
	return (1);
}
