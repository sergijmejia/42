/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:55:01 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/31 17:01:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que cuenta la catidad de nodos del mapa*/
static int	count_nodes(int fd)
{
	int		count;
	char	*line;
	int		i;
	int		word;

	count = 0;
	lseek(fd, 0, SEEK_SET);
	line = get_next_line(fd);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	while (line != NULL)
	{
		word = 0;
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
				word++;
			i++;
		}
		count = count + word;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

/*Funcion para guardar los datos de los nodos de cada linea del mapa*/
static void	get_info_nodes(t_image_data *image, char **s, int i, int *old_len)
{
	char	**split_color;

	split_color = ft_split(s[i], ',');
	image->map[*old_len + i].z = ft_atoi(split_color[0]);
	if (split_color[1] != NULL)
	{
		image->map[*old_len + i].r = get_color("red", split_color[1]);
		image->map[*old_len + i].g = get_color("green", split_color[1]);
		image->map[*old_len + i].b = get_color("blue", split_color[1]);
	}
	else
	{
		image->map[*old_len + i].r = 255;
		image->map[*old_len + i].g = 255;
		image->map[*old_len + i].b = 255;
	}
	image->map[*old_len + i].net_x = 0;
	image->map[*old_len + i].net_y = 0;
	if (i > 0)
		image->map[*old_len + i].net_x = 1;
	if (i < image->len_line)
		image->map[*old_len + i].net_y = 1;
	ft_clean_split(split_color);
}

/*Funcion que gestiona cada una de las lineas archivo de texto y lo almacena 
en el mapa*/
static void	create_map(t_image_data *image, char *line, int j, int *old_len)
{
	char	**split_line;
	int		len;
	int		i;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return ;
	len = 0;
	while (split_line[len] != NULL)
		len++;
	i = 0;
	while (i < len)
	{
		image->map[*old_len + i].x = i;
		image->map[*old_len + i].y = j;
		get_info_nodes(image, split_line, i, old_len);
		i++;
	}
	ft_clean_split(split_line);
	image->len_line = len;
	*old_len = *old_len + len;
}

/*Funcion para crear el array con las coordenadas de los puntos del mapa*/
void	create_matrix(int fd, t_image_data *image)
{
	char	*line;
	int		old_len;
	int		j;

	old_len = 0;
	j = 0;
	image->len = count_nodes(fd);
	image->map = (t_pixel_data *) malloc (sizeof(t_pixel_data) * (image->len));
	lseek(fd, 0, SEEK_SET);
	line = get_next_line(fd);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	while (line != NULL)
	{
		create_map(image, line, j, &old_len);
		free(line);
		line = get_next_line(fd);
		if (line != NULL && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		j++;
	}
	image->iso_x_moved = (int *) malloc (sizeof(int) * image->len);
	image->iso_y_moved = (int *) malloc (sizeof(int) * image->len);
	iso_matrix(image);
	perspective_matrix(image, 200.0);
}
