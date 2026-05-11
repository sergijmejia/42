/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:27:33 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:27:38 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
#include "libft.h"

/**
 * @brief Sets color and brightness properties for the light node.
 * @param t Split string array containing light data.
 * @param node Pointer to the light node being populated.
 * @return int 1 if valid, 0 if color parsing fails or ratio is out of range.
 */
static int	fill_light_data(char **t, t_light_node *node)
{
	node->ratio = ft_atod(t[2]);
	if (node->ratio < 0.0 || node->ratio > 1.0)
		return (0);
	if (split_len(t) == 4)
	{
		if (!parse_color(t[3], &node->color))
			return (0);
	}
	else
	{
		node->color.r = 255;
		node->color.g = 255;
		node->color.b = 255;
	}
	return (1);
}

/**
 * @brief Parse ambient light line A.
 * @param t Token array for one line.
 * @param s Scene to update.
 * @return 1 on success, 0 on duplicate or invalid data.
 */
int	parse_ambient(char **t, t_scene *s)
{
	if (split_len(t) != 3 || s->has_ambient)
		return (0);
	s->ambient.ratio = ft_atod(t[1]);
	if (s->ambient.ratio < 0.0 || s->ambient.ratio > 1.0)
		return (0);
	if (!parse_color(t[2], &s->ambient.color))
		return (0);
	s->has_ambient = 1;
	return (1);
}

/**
 * @brief Parse camera line C.
 * @param t Token array for one line.
 * @param s Scene to update.
 * @return 1 on success, 0 on duplicate or invalid data.
 */
int	parse_camera(char **t, t_scene *s)
{
	if (split_len(t) != 4 || s->has_camera)
		return (0);
	if (!parse_vec(t[1], &s->camera.pos) || !parse_vec(t[2], &s->camera.dir))
		return (0);
	if (vec_len(s->camera.dir) < 1e-9)
		return (0);
	s->camera.dir = vec_norm(s->camera.dir);
	s->camera.fov = ft_atoi(t[3]);
	if (s->camera.fov < 0 || s->camera.fov > 180)
		return (0);
	s->has_camera = 1;
	return (1);
}

/**
 * @brief Parses light data from a string array and adds it to the scene.
 * @param t Split string array with light parameters.
 * @param s Pointer to the scene structure.
 * @return int 1 if success, 0 if any parsing or memory error occurs.
 */
int	parse_light(char **t, t_scene *s)
{
	t_light_node	*node;

	if (split_len(t) < 3 || split_len(t) > 4)
		return (0);
	if (s->has_light)
		return (bonus_append_light(t, s));
	node = malloc(sizeof(*node));
	if (!node)
		return (0);
	if (!parse_vec(t[1], &node->pos) || !fill_light_data(t, node))
	{
		free(node);
		return (0);
	}
	node->next = s->lights;
	s->lights = node;
	s->has_light = 1;
	return (1);
}
