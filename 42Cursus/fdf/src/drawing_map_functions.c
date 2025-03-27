/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:30:21 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/27 16:50:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion que devuelve la posicion en que se encuentra c en str*/
static int	hexapos(const char *str, char c)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == ((char) ft_tolower(c)))
			return (i);
		i++;
	}
	return (0);
}

/*Funcion que transforma un string hexadecimal en entero*/
static int	hexa_to_int(char *s, int len)
{
	int	number;
	int	i;

	i = 0;
	number = 0;
	while (i < len)
	{
		if (ft_strcontains("0123456789abcdef", (char) ft_tolower(s[i])))
			number = number * 16 + hexapos("0123456789abcdef", s[i]);
		else
			return (0);
		i++;
	}
	return (number);
}

/*Funcion para dibujar el mapa de la matriz*/
void	draw_map(t_image_data *image, int clear)
{
	int				i;
	int				len;
	int				len_line;
	t_pixel_data	*map_points;

	len_line = image->len_line;
	len = image->len;
	map_points = image->map;
	i = 1;
	while (i < len)
	{
		if (map_points[i].net_x)
			draw_line(image, map_points[i - 1], map_points[i], clear);
		if (map_points[i].net_y)
			draw_line(image, map_points[i - len_line], map_points[i], clear);
		i++;
	}
}

/*Funcion para limpiar la imagen*/
void	clear_image(t_image_data *image)
{
	int				i;
	int				len;
	int				len_line;
	t_pixel_data	*map_points;

	len_line = image->len_line;
	len = image->len;
	map_points = image->map;
	i = 1;
	while (i < len)
	{
		if (map_points[i].net_x)
			draw_line(image, map_points[i - 1], map_points[i], 1);
		if (map_points[i].net_y)
			draw_line(image, map_points[i - len_line], map_points[i], 1);
		i++;
	}
}

/*Funcion para obtener los colores rgb a partir de un formato hexadecimal con
prefijo*/
int	get_color(char const *s, char *color)
{
	char	*color_trimmed;
	char	trim_string[3];
	char	*one_color;
	int		i;
	int		number;

	ft_strlcpy(&trim_string[0], "0x", 3);
	color_trimmed = ft_strtrim(color, trim_string);
	if (ft_strncmp("blue", s, 5) == 0)
		i = 0;
	else if (ft_strncmp("green", s, 6) == 0)
		i = 2;
	else if (ft_strncmp("red", s, 4) == 0)
		i = 4;
	number = 0;
	if (i < ((int) ft_strlen(color_trimmed)))
	{
		one_color = (char *) malloc (sizeof(char *) * 3);
		ft_strlcpy(one_color, &(color_trimmed[i]), 3);
		one_color[2] = '\0';
		number = hexa_to_int(one_color, 2);
		free(one_color);
	}
	return (number);
}
