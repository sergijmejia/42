/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 20:16:16 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 20:16:19 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
#include "libft.h"

#define RT_READ_CHUNK 65536
#define RT_MAX_BYTES 16777216 
//#define RT_MAX_BYTES (16 * 1024 * 1024)

/**
 * @brief Normalize whitespace, skip comments/empty, parse one line.
 * @param line Mutable single line (tabs to spaces; leading trim).
 * @param scene Target scene.
 * @return 1 if line ok or ignorable, 0 on parse failure.
 */
static int	process_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		ok;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		else if (line[i] == '\r')
			line[i] = ' ';
		i++;
	}
	while (*line && is_space(*line))
		line++;
	if (!*line || *line == '\n')
		return (1);
	if (*line == '#')
		return (1);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	ok = parse_tokens(tokens, scene);
	free_split(tokens);
	return (ok);
}

/**
 * @brief Checks if all mandatory elements (A, C, L) are present in the scene.
 * @param scene Pointer to the scene structure.
 * @return int 1 if valid, 0 if any mandatory element is missing.
 */
static int	validate_mandatory(t_scene *scene)
{
	if (scene->has_ambient != 1 || scene->has_camera != 1
		|| scene->has_light != 1)
		return (put_error("A, C and L are mandatory"));
	return (1);
}

/**
 * @brief Processes the buffer line by line to build the scene.
 * @param buffer Raw string buffer from the .rt file.
 * @param scene Pointer to the scene structure.
 * @return int 1 if success, 0 if an error occurs.
 */
static int	process_buffer(char *buffer, t_scene *scene)
{
	int		i;
	int		j;
	char	line[1024];

	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (buffer[i] && buffer[i] != '\n' && j < 1023)
		{
			if (buffer[i] == '\r')
				i++;
			else
				line[j++] = buffer[i++];
		}
		if (buffer[i] == '\n')
			i++;
		line[j] = '\0';
		if (!process_line(line, scene))
			return (put_error("Invalid scene element"));
	}
	return (validate_mandatory(scene));
}

/**
 * @brief Load and parse a .rt scene file into a scene structure.
 * @param path Path to the scene file.
 * @param scene Uninitialized scene; filled on success.
 * @return 1 on success, 0 on any error.
 */
int	parse_rt_file(const char *path, t_scene *scene)
{
	int		fd;
	char	*buf;
	int		ok;

	if (!path || !has_rt_extension(path))
		return (put_error("Invalid .rt file name"));
	init_scene_struct(scene);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (put_error("Cannot open .rt file"));
	buf = read_rt_full(fd);
	close(fd);
	if (!buf)
		return (put_error("Cannot read .rt file"));
	if (!buf[0])
	{
		free(buf);
		return (put_error("Empty .rt file"));
	}
	ok = process_buffer(buf, scene);
	free(buf);
	if (!ok)
		return (parse_error_cleanup(scene));
	return (1);
}
