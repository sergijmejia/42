/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:28:22 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:28:25 by smejia-a         ###   ########.fr       */
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
 * @brief Expands the buffer capacity using realloc and checks for limits.
 * @param buf Pointer to the current buffer.
 * @param cap Pointer to the current capacity.
 * @param len Current length of the data in buffer.
 * @return New buffer pointer or NULL on failure or limit reached.
 */
static char	*expand_rt_buf(char *buf, size_t *cap, size_t len)
{
	char	*tmp;

	if (*cap >= (size_t)RT_MAX_BYTES)
		return (NULL);
	*cap *= 2;
	if (*cap > (size_t)RT_MAX_BYTES)
		*cap = (size_t)RT_MAX_BYTES;
	if (len + RT_READ_CHUNK > *cap)
		return (NULL);
	tmp = realloc(buf, *cap + 1);
	if (!tmp)
		free(buf);
	return (tmp);
}

/**
 * @brief Handles the final steps of the reading process.
 * @param buf The allocated buffer.
 * @param len Total bytes read.
 * @param n Last return value from read().
 * @return The null-terminated buffer or NULL if a read error occurred.
 */
static char	*finish_read(char *buf, size_t len, ssize_t n)
{
	if (n < 0)
	{
		free(buf);
		return (NULL);
	}
	buf[len] = '\0';
	return (buf);
}

/**
 * @brief Read entire file into one malloc’d NUL-terminated string.
 * @param fd Open readable file descriptor.
 * @return Allocated buffer or NULL on read/alloc error or size limit exceeded.
 */
char	*read_rt_full(int fd)
{
	size_t	cap;
	size_t	len;
	ssize_t	n;
	char	*buf;

	cap = (size_t)RT_READ_CHUNK;
	len = 0;
	buf = malloc(cap + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		if (len + RT_READ_CHUNK > cap)
		{
			buf = expand_rt_buf(buf, &cap, len);
			if (!buf)
				return (NULL);
		}
		n = read(fd, buf + len, RT_READ_CHUNK);
		if (n <= 0)
			break ;
		len += (size_t)n;
	}
	return (finish_read(buf, len, n));
}

/**
 * @brief Clears scene lists and returns 0.
 * @param scene Pointer to the scene structure.
 * @return int Always 0.
 */
int	parse_error_cleanup(t_scene *scene)
{
	scene_lights_clear(scene);
	scene_objects_clear(scene);
	return (0);
}
