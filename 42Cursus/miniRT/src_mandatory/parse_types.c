/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:28:53 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:28:54 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
#include "libft.h"

/**
 * @brief Parse a three-component vector from comma-separated values.
 * @param str String "x,y,z" with no spaces inside components.
 * @param v Output storage for the vector.
 * @return 1 on success, 0 on invalid format.
 */
int	parse_vec(char *str, t_vec *v)
{
	char	**xyz;

	xyz = ft_split(str, ',');
	if (!xyz || split_len(xyz) != 3)
		return (free_split(xyz), 0);
	v->x = ft_atod(xyz[0]);
	v->y = ft_atod(xyz[1]);
	v->z = ft_atod(xyz[2]);
	free_split(xyz);
	return (1);
}

/**
 * @brief Parse an RGB triplet and validate 0-255 per channel.
 * @param str String "r,g,b" with integer components.
 * @param c Output color.
 * @return 1 on success, 0 on parse error or out-of-range value.
 */
int	parse_color(char *str, t_color *c)
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
 * @brief Verify the file path has a .rt suffix.
 * @param path Path string to validate.
 * @return 1 if the last three characters are .rt, otherwise 0.
 */
int	has_rt_extension(const char *path)
{
	int	len;

	len = 0;
	while (path[len])
		len++;
	if (len < 4)
		return (0);
	if (path[len - 3] != '.')
		return (0);
	if (path[len - 2] != 'r')
		return (0);
	if (path[len - 1] != 't')
		return (0);
	return (1);
}

/**
 * @brief Zeroes out the scene structure mandatory flags and pointers.
 * @param scene Pointer to the scene structure.
 * @return None.
 */
void	init_scene_struct(t_scene *scene)
{
	scene->has_ambient = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
	scene->lights = NULL;
	scene->objects = NULL;
}
