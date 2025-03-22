/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:15:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/22 14:31:55 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion para dibujar el mapa de la matriz*/
void	design_map(t_image_data *image, int clear)
{
	int				i;
	int				len;
	int				len_line;
	//mlx_image_t		*img;
	t_pixel_data	*map_points;

	len_line = image->len_line;
	len = image->len;
	//img = image->img;
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
	//mlx_image_t		*img;
	t_pixel_data	*map_points;

	len_line = image->len_line;
	len = image->len;
	//img = image->img;
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

/*Funcion que devuelve la posicion en que se encuentra c en str*/
int	hexapos(const char *str, char c)
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
int	hexa_to_int(char *s, int len)
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


/*Funcion para obtener los colores rgb a partir de un formato hexadecimal con
prefijo*/
int	get_color(char const *s, char *color)
{
	char	*color_trimmed;
	char	trim_string[3];
	char	*one_color;
	int		i;
	int		number;

	trim_string[0] = '0';
	trim_string[1] = 'x';
	trim_string[2] = '\0';
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

/*Funcion de libearacion de memoria de la matriz*/
t_pixel_data	*ft_clean_map(t_pixel_data **pixel)
{
	free(*pixel);
	*pixel = NULL;
	return (NULL);
}

/*Funcion de libearacion de memoria del split*/
char	*ft_clean_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}

/*Funcion para encontrar el valor maximo de un array de float*/
float	ft_max_float(float *cord, int len)
{
	float	max;
	int		i;

	max = cord[0];
	i = 0;
	while (i < len)
	{
		if (cord[i] > max)
			max = cord[i];
		i++;
	}
	return (max);
}

/*Funcion para encontrar el valor minimo de un array de flat*/
float	ft_min_float(float *cord, int len)
{
	float	min;
	int		i;

	min = cord[0];
	i = 0;
	while (i < len)
	{
		if (cord[i] < min)
			min = cord[i];
		i++;
	}
	return (min);
}

/*Funcion que calcula la proyecccion isometrica x sin transformar*/
float	*proj_iso_x(t_pixel_data *map_points, int len)
{
	int		x;
	int		y;
	int		i;
	float	*iso_x;

	i = 0;
	iso_x = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		x = 12 * map_points[i].x;
		y = 12 * map_points[i].y;
		iso_x[i] = (x - y) * cos(M_PI / 6);
		i++;
	}
	return (iso_x);
}

/*Funcion que calcula la proyeccion isometrica y sin transformar*/
float	*proj_iso_y(t_pixel_data *map_points, int len)
{
	int		x;
	int		y;
	int		z;
	int		i;
	float	*iso_y;

	i = 0;
	iso_y = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		x = 12 * map_points[i].x;
		y = 12 * map_points[i].y;
		z = map_points[i].z;
		iso_y[i] = (-1) * (z) + (x + y) * sin(M_PI / 6);
		i++;
	}
	return (iso_y);
}

/*Funcion que transforma las proyecciones isometricas con proporcion en eje x*/
void	transf_iso_matrix_prop_x(t_pixel_data *map_points, t_proj_data data, float *iso_x, float *iso_y, int len)
{
	int		i;
	float	dx;
	float	sy;
	float	x;
	float	y;

	i = 0;
	dx = data.max_iso_x - data.min_iso_x;
	sy = data.max_iso_y + data.min_iso_y;
	while (i < len)
	{
		x = 1 + 38.0 * (iso_x[i] - data.min_iso_x) / dx;
		y = (19.0 * WIDTH) * (2 * iso_y[i] - sy) / (40.0 * dx);
		map_points[i].iso_x = (int)(WIDTH * x / 40.0);
		map_points[i].iso_y = (int)(y + (HEIGHT / 2));
		i++;
	}
}

/*Funcion que transforma las proyecciones isometricas con proporcion en eje y*/
void	transf_iso_matrix_prop_y(t_pixel_data *map_points, t_proj_data data, float *iso_x, float *iso_y, int len)
{
	int		i;
	float	dy;
	float	sx;
	float	x;
	float	y;

	i = 0;
	dy = data.max_iso_y - data.min_iso_y;
	sx = data.max_iso_x + data.min_iso_x;
	while (i < len)
	{
		x = (19.0 * HEIGHT) * (2 * iso_x[i] - sx) / (40.0 * dy);
		y = 1 + 38.0 * (iso_y[i] - data.min_iso_y) / dy;
		map_points[i].iso_y = (int)(HEIGHT * y / 40.0);
		map_points[i].iso_x = (int)(x + (WIDTH / 2));
		i++;
	}
}

/*Funcion para calcular las proyecciones isometricas de una matriz de puntos*/
void	iso_matrix(t_image_data *image)
{
	t_proj_data	data;
	float				*iso_x;
	float				*iso_y;
	float				prop_x;
	float				prop_y;

	iso_x = proj_iso_x(image->map, image->len);
	iso_y = proj_iso_y(image->map, image->len);
	data.max_iso_x = ft_max_float(iso_x, image->len);
	data.min_iso_x = ft_min_float(iso_x, image->len);
	data.max_iso_y = ft_max_float(iso_y, image->len);
	data.min_iso_y = ft_min_float(iso_y, image->len);
	prop_x = (data.max_iso_x - data.min_iso_x) / WIDTH;
	prop_y = (data.max_iso_y - data.min_iso_y) / HEIGHT;
	if (prop_x > prop_y)
		transf_iso_matrix_prop_x(image->map, data, iso_x, iso_y, image->len);
	else
		transf_iso_matrix_prop_y(image->map, data, iso_x, iso_y, image->len);
	free(iso_x);
	free(iso_y);
}


/*void perspective_transform(t_pixel_data *map_points, t_isometric_data data, float *iso_x, float *iso_y, int len, int vanishing_x, int vanishing_y, double projection_distance) {
    int i;
    float dx;
    float dy;
    float distance;
    float scale;
    float x;
    float y;

    i = 0;
    while (i < len) {
        dx = iso_x[i] - (data.min_x + (data.max_x-data.min_x)/2); // centro el mapa
        dy = iso_y[i] - (data.min_y + (data.max_y-data.min_y)/2); // centro el mapa

        distance = sqrt(dx * dx + dy * dy); // Distancia al centro del mapa.

        scale = projection_distance / (projection_distance + distance); // escala dependiendo de la distancia.

        x = vanishing_x + dx * scale * 40; // multiplica por un factor para ajustar la escala.
        y = vanishing_y + dy * scale * 40;

        map_points[i].iso_x = (int)x;
        map_points[i].iso_y = (int)y;
        i++;
    }
}*/

//asummo la camara en la posicion (100, 100, 500) y la distancia 800

/*Funcion que calcula la proyecccion con perspectiva x sin transformar*/
float	*proj_pers_x(t_pixel_data *map_points, int len, double d)
{
	float	x;
	float	z;
	int		i;
	float	cx;
	float	cz;
	float	*pers_x;

	i = 0;
	cx = -650;
	cz = 10000;
	//printf("en proj_pers_x recibo d = %f\n", d);
	pers_x = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		x = (float) map_points[i].x;
		z = (float) map_points[i].z;
		if (z == cz)
			pers_x[i] = 4 * (x - cx) * d;
		else
			pers_x[i] = ((x - cx) / (cz -z)) * d;
		//printf("El valor de x[%d] = %f\n", i, pers_x[i]);
		i++;
	}
	return (pers_x);
}

/*Funcion que calcula la proyeccion isometrica y sin transformar*/
float	*proj_pers_y(t_pixel_data *map_points, int len, double d)
{
	float	y;
	float	z;
	int		i;
	float	cy;
	float	cz;
	float	*pers_y;

	i = 0;
	cy = 2250;
	cz = 10000;
	//printf("en proj_pers_y recibo d = %f\n", d);
	pers_y = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		y = (float) map_points[i].y;
		z = (float) map_points[i].z;
		if (z == cz)
		{
			pers_y[i] = 4 * (y - cy) * d;
			//printf("Entra en opcion 1. cy = %f, cz = %f, y = %f, z = %f, d = %f, y guarda %f\n", cy, cz, y, z, d, pers_y[i]);
		}
		else
		{
			pers_y[i] = ((y - cy) / (cz -z)) * d;
			//printf("Entra en opcion 2. cy = %f, cz = %f, y = %f, z = %f, d = %f, y guarda %f\n", cy, cz, y, z, d, pers_y[i]);
		}
		i++;
	}
	return (pers_y);
}






/*Funcion que transforma las proyecciones en perspectiva con proporcion en eje x*/
void	transf_pers_matrix_prop_x(t_pixel_data *map_points, t_proj_data data, float *pers_x, float *pers_y, int len)
{
	int		i;
	float	dx;
	float	sy;
	float	x;
	float	y;

	i = 0;
	dx = data.max_pers_x - data.min_pers_x;
	sy = data.max_pers_y + data.min_pers_y;
	while (i < len)
	{
		x = 1 + 38.0 * (pers_x[i] - data.min_pers_x) / dx;
		y = (19.0 * WIDTH) * (2 * pers_y[i] - sy) / (40.0 * dx);
		map_points[i].pers_x = (int)(WIDTH * x / 40.0);
		map_points[i].pers_y = (int)(y + (HEIGHT / 2));
		i++;
	}
}

/*Funcion que transforma las proyecciones en perspectiva con proporcion en eje y*/
void	transf_pers_matrix_prop_y(t_pixel_data *map_points, t_proj_data data, float *pers_x, float *pers_y, int len)
{
	int		i;
	float	dy;
	float	sx;
	float	x;
	float	y;

	i = 0;
	dy = data.max_pers_y - data.min_pers_y;
	sx = data.max_pers_x + data.min_pers_x;
	while (i < len)
	{
		x = (19.0 * HEIGHT) * (2 * pers_x[i] - sx) / (40.0 * dy);
		y = 1 + 38.0 * (pers_y[i] - data.min_pers_y) / dy;
		map_points[i].pers_y = (int)(HEIGHT * y / 40.0);
		map_points[i].pers_x = (int)(x + (WIDTH / 2));
		i++;
	}
}

void	perspective_matrix(t_image_data *image, double d_projection)
{
	t_proj_data	data;
	float	*pers_x;
    float	*pers_y;
	float	prop_x;
	float	prop_y;

    pers_x = proj_pers_x(image->map, image->len, d_projection);
    pers_y = proj_pers_y(image->map, image->len, d_projection);
	data.max_pers_x = ft_max_float(pers_x, image->len);
    data.min_pers_x = ft_min_float(pers_x, image->len);
    data.max_pers_y = ft_max_float(pers_y, image->len);
    data.min_pers_y = ft_min_float(pers_y, image->len);
    prop_x = (data.max_pers_x - data.min_pers_x) / WIDTH;
    prop_y = (data.max_pers_y - data.min_pers_y) / HEIGHT;
	if (prop_x > prop_y)
		transf_pers_matrix_prop_x(image->map, data, pers_x, pers_y, image->len);
	else
		transf_pers_matrix_prop_y(image->map, data, pers_x, pers_y, image->len);
    free(pers_x);
    free(pers_y);
}

/*Funcion para modificar la longitud del array de coordendas*/
t_pixel_data	*realloc_map(t_image_data *image, int old_len)
{
	t_pixel_data	*new_map;
	int				i;

	new_map = (t_pixel_data *) malloc (sizeof(t_pixel_data) * image->len);
	i = 0;
	while (i < old_len)
	{
		new_map[i] = image->map[i];
		i++;
	}
	free(image->map);
	return (new_map);
}

/*Funcion para copiar la memoria de un mapa a otro*/
t_pixel_data	*copy_map(t_pixel_data *map_points, int len)
{
	int				i;
	t_pixel_data	*home_map_points;

	home_map_points = (t_pixel_data *) malloc (sizeof(t_pixel_data) * len);
	if (!home_map_points)
		return (NULL);
	i = 0;
	while (i < len)
	{
		home_map_points[i] = map_points[i];
		i++;
	}
	return (home_map_points);
}

/*Funcion para contar palabras*/
int	countwords(const char *s, char c)
{
	int	i;
	int	word;

	if (s == NULL || s[0] == '\0')
		return (0);
	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

/*Funcion que cuenta la catidad de nodos del mapa*/
int	count_nodes(int fd)
{
	int		count;
	char	*line;

	count = 0;
	lseek(fd, 0, SEEK_SET);
	line = get_next_line(fd);
	if (line[ft_strlen(line)- 1] == '\n')
		 line[ft_strlen(line)- 1] = '\0';
	while (line != NULL)
	{
		count = count + countwords(line, ' ');
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

/*Funcion para crear el array con las coordenadas de los puntos del mapa*/
void	create_matrix(int fd, t_image_data *image)
{
	char	*line;
	//char	*line_trimmed;
	//char	*trim_char;
	char	**split_line;
	char	**split_color;
	int		len;
	int		old_len;
	int		i;
	int		j;

	old_len = 0;
	image->len_line = 0;
	j = 0;
	printf("Entra en la funcion count_nodes\n");
	image->len = count_nodes(fd);
	printf("La longitud del array es: %d\n", image->len);
	image->map = (t_pixel_data *) malloc (sizeof(t_pixel_data) * (image->len));
	lseek(fd, 0, SEEK_SET);
	line = get_next_line(fd);
	if (line[ft_strlen(line)- 1] == '\n')
		line[ft_strlen(line)- 1] = '\0';
	while (line != NULL)
	{
		split_line = ft_split(line, ' ');
		if (!split_line)
			return ;
		len = 0;
		while (split_line[len] != NULL)
			len++;
		i = 0;
		while (i < len)
		{
			image->map[old_len + i].x = i;
			image->map[old_len + i].y = j;
			split_color = ft_split(split_line[i], ',');
			//printf("nodo %d, z = %s, color = %s\n", i, split_color[0], split_color[1]);
			//image->map[old_len + i].z = ft_atoi(split_line[i]);
			image->map[old_len + i].z = ft_atoi(split_color[0]);
			if (split_color[1] != NULL)
			{
				image->map[old_len + i].r = get_color("red", split_color[1]);
				image->map[old_len + i].g = get_color("green", split_color[1]);
				image->map[old_len + i].b = get_color("blue", split_color[1]);
			}
			else
			{
				image->map[old_len + i].r = 255;
				image->map[old_len + i].g = 255;
				image->map[old_len + i].b = 255;
			}
			image->map[old_len + i].net_x = 0;
			image->map[old_len + i].net_y = 0;
			if (i > 0)
				image->map[old_len + i].net_x = 1;
			if (i < image->len_line)
			{
				image->map[old_len + i].net_y = 1;
				//printf("net_y puesto a 1\n");
			}
			//printf("Va a hacer un free split_color");
			ft_clean_split(split_color);
			i++;
		}
		//printf("Va a hacer un free line");
		free(line);
		//free(line_trimmed);
		ft_clean_split(split_line);
		line = get_next_line(fd);
		//line_trimmed = ft_strtrim(line, trim_char);
		if (line != NULL && line[ft_strlen(line)- 1] == '\n')
			line[ft_strlen(line)- 1] = '\0';
		image->len_line = len;
		old_len = old_len + len;

		j++;
	}
	image->iso_x_moved = (int *) malloc (sizeof(int) * image->len);
	image->iso_y_moved = (int *) malloc (sizeof(int) * image->len);
	iso_matrix(image);
	perspective_matrix(image, 200.0);
}

/*Funcion para dibujar el mapa de la matriz
void	design_map(t_image_data *image, int clear)
{
	int				i;
	int				len;
	int				len_line;
	mlx_image_t		*img;
	t_pixel_data	*map_points;

	len_line = image->len_line;
	len = image->len;
	img = image->img;
	map_points = image->map;
	i = 1;
	while (i < len)
	{
		if (map_points[i].net_x)
			draw_line(img, map_points[i - 1], map_points[i], clear);
		if (map_points[i].net_y)
			draw_line(img, map_points[i - len_line], map_points[i], clear);
		i++;
	}
}*/

/*Funcion que gestiona el comportamiento de la barra espaciadora*/
void	ft_space_key(t_image_data *image)
{	
	free(image->map);
	if (image->iso_pers == 0)
	{
		mlx_delete_image(image->mlx, image->img_iso);
		image->map = copy_map(image->home_map, image->len);
		image->img_iso = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		design_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
	}
	else
	{
		mlx_delete_image(image->mlx, image->img_iso);
		image->map = copy_map(image->home_map, image->len);
		image->img_pers = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		design_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_pers, 0, 0);
	}
}

/*Funcion para realizar la rotacion respecto al movimiento del cursor*/
void	ft_image_rotation(t_image_data *image, double xpos, double ypos)
{
	//t_pixel_data	*new_map;
	static struct timespec	last_update;
	struct timespec			current_time;
	double					elapsed_time;
	int				i;
	static int32_t	x0;
	static int32_t	y0;
	double			x_rel;
	double			y_rel;
	//double			x_new;
	//double			y_new;
	double			theta0;
	static double	theta0_mod = 0.0;
	double			theta1;
	double			theta;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	elapsed_time = (current_time.tv_sec - last_update.tv_sec) + (current_time.tv_nsec - last_update.tv_nsec) / 1e9;
	if (elapsed_time >= 1.0 / 60.0)
	{
		if (image->start_rotation == 1)
		{
			if (image->mod == 1)
				mlx_get_mouse_pos(image->mlx, &x0, &y0);
			else
			{
				x0 = WIDTH / 2;
				y0 = HEIGHT / 2;
			}
			image->start_rotation = 0;
			theta0_mod = 0.0;
		}
		if (image->mod == 1)
			theta0 = theta0_mod;
		else
			theta0 = atan2(image->old_y - y0, image->old_x - x0);
		//new_map = copy_map(image->map, image->len);
		i = 0;
		theta1 = atan2(ypos - y0, xpos - x0);
		theta = theta1 - theta0;
		if (image->mod == 1)
			theta0_mod = theta1;
		image->old_x = (int32_t) xpos;
		image->old_y = (int32_t) ypos;
		clear_image(image);
		while (i < image->len)
		{
			x_rel = image->map[i].iso_x - x0;
			y_rel = image->map[i].iso_y - y0;
			image->map[i].iso_x = x_rel * cos(theta) - y_rel * sin(theta) + x0;
			image->map[i].iso_y = x_rel * sin(theta) + y_rel * cos(theta) + y0;
			//new_map[i].iso_x = x_new + x0;
			//new_map[i].iso_y = y_new + y0;
			i++;
		}
		//clear_image(image);
		//free(image->map);
		//mlx_delete_image(image->mlx, image->img);
		//image->map = new_map;
		//image->img = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		//design_map(image->map, image->img, image->len, image->len_line);
		design_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
		clock_gettime(CLOCK_MONOTONIC, &last_update);
	}
}

/*Funcion para realizar la traslacion respecto al movimiento del cursor*/
void	ft_image_traslation(t_image_data *image, double xpos, double ypos)
{
	//t_pixel_data	*new_map;
	static struct timespec	last_update;
	struct timespec			current_time;
	double					elapsed_time;
	double			dx;
	double			dy;
	int				i;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	elapsed_time = (current_time.tv_sec - last_update.tv_sec) + (current_time.tv_nsec - last_update.tv_nsec) / 1e9;
	if (elapsed_time >= 1.0 / 60.0)
	{
		//new_map = copy_map(image->map, image->len);
		//printf("Entra en la traslacion\n");
		dx = xpos - image->old_x;
		dy = ypos - image->old_y;
		image->old_x = (int32_t) xpos;
		image->old_y = (int32_t) ypos;
		i = 0;
		/*while (i < image->len)
		{
			new_map[i].iso_x = image->map[i].iso_x + dx;
			new_map[i].iso_y = image->map[i].iso_y + dy;
			i++;
		}*/
		/*while (i < image->len)
		{
			image->iso_x_moved[i] = image->map[i].iso_x + dx;
			image->iso_y_moved[i] = image->map[i].iso_y + dy;
		}*/
		clear_image(image);
		//free(image->map);
		//printf("Limpia la imagen\n");
		while (i < image->len)
		{
			image->map[i].iso_x = image->map[i].iso_x + dx;
			image->map[i].iso_y = image->map[i].iso_y + dy;
			i++;
		}
		//mlx_delete_image(image->mlx, image->img);
		//image->map = new_map;
		//image->img = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		//design_map(image->map, image->img, image->len, image->len_line);
		design_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
		clock_gettime(CLOCK_MONOTONIC, &last_update);
	}
}

/*Funcion que gestiona el comportamiento cuando el cursor se mueve*/
void	ft_chook(double xpos, double ypos, void *par)
{
	t_image_data	*image;

	image = (t_image_data *) par;
	if (image->is_dragging)
	{
		if (image->translate)
			ft_image_traslation(image, xpos, ypos);
		else if (image->rotate)
			ft_image_rotation(image, xpos, ypos);
	}
}

/*Funcion que gestiona el comportamiento del boton izquierdo del mouse*/
void	ft_mouse_left(action_t act, modifier_key_t mod, t_image_data *image)
{
	int32_t			old_x;
	int32_t			old_y;

	if (act == MLX_PRESS)
	{
		if (mod == MLX_SHIFT)
			image->mod = 1;
		else
			image->mod = 0;
		mlx_get_mouse_pos(image->mlx, &old_x, &old_y);
		image->old_x = old_x;
		image->old_y = old_y;
		image->is_dragging = 1;
		image->translate = 1;
		image->mouse = MLX_MOUSE_HIDDEN;
		mlx_set_cursor_mode(image->mlx, image->mouse);
	}
	else if (act == MLX_RELEASE)
	{
		image->is_dragging = 0;
		image->translate = 0;
		image->mod = 0;
		image->mouse = MLX_MOUSE_NORMAL;
		mlx_set_cursor_mode(image->mlx, image->mouse);
	}
}

/*Funcion que gestiona el comportamiento del boton derecho del mouse*/
void	ft_mouse_right(action_t act, modifier_key_t mod, t_image_data *image)
{
	int32_t	initial_x;
	int32_t	initial_y;

	if (act == MLX_PRESS)
	{
		if (mod == MLX_SHIFT)
			image->mod = 1;
		else
			image->mod = 0;
		mlx_get_mouse_pos(image->mlx, &initial_x, &initial_y);
		image->old_x = initial_x;
		image->old_y = initial_y;
		image->is_dragging = 1;
		image->rotate = 1;
		image->mouse = MLX_MOUSE_HIDDEN;
		mlx_set_cursor_mode(image->mlx, image->mouse);
	}
	else if (act == MLX_RELEASE)
	{
		image->is_dragging = 0;
		image->rotate = 0;
		image->start_rotation = 1;
		image->mod = 0;
		image->mouse = MLX_MOUSE_NORMAL;
		mlx_set_cursor_mode(image->mlx, image->mouse);
	}
}

/*Funcion que gestiona el comportamiento de la letra a para cambiar de mapas*/
void	ft_a_key(t_image_data *image)
{
	free(image->map);
	if (image->iso_pers == 0)
	{
		image->iso_pers = 1;
		mlx_delete_image(image->mlx, image->img_iso);
		image->img_pers = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		design_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_pers, 0, 0);
	}
	else
	{
		image->iso_pers = 0;
		mlx_delete_image(image->mlx, image->img_pers);
		image->img_iso = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		design_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
	}
}


/*Funcion que gestiona el comportamiento de teclas del mouse*/
void	ft_mhook(mouse_key_t key, action_t act, modifier_key_t mod, void *par)
{
	t_image_data	*image;

	image = (t_image_data *) par;
	if (key == MLX_MOUSE_BUTTON_LEFT)
		ft_mouse_left(act, mod, image);
	if (key == MLX_MOUSE_BUTTON_RIGHT)
		ft_mouse_right(act, mod, image);
}

/*Funcion que gestiona el comportamiento de ciertas teclas del teclado*/
void	ft_khook(mlx_key_data_t key_hook, void *param)
{
	t_image_data	*image;

	image = (t_image_data *) param;
	if (key_hook.key == MLX_KEY_ESCAPE)
		mlx_close_window(image->mlx);
	if (key_hook.key == MLX_KEY_UP)
		ft_image_traslation(image, image->old_x, image->old_y - 10);
	if (key_hook.key == MLX_KEY_DOWN)
		ft_image_traslation(image, image->old_x, image->old_y + 10);
	if (key_hook.key == MLX_KEY_LEFT)
		ft_image_traslation(image, image->old_x - 10, image->old_y);
	if (key_hook.key == MLX_KEY_RIGHT)
		ft_image_traslation(image, image->old_x + 10, image->old_y);
	if (key_hook.key == MLX_KEY_SPACE)
		ft_space_key(image);
	if (key_hook.key == MLX_KEY_A)
		ft_a_key(image);
}

/*Funcion que gestiona el zoom de la imagen*/
void	ft_zoom(t_image_data *image, double delta, int32_t x, int32_t y)
{
	static struct timespec	last_update;
	struct timespec			current_time;
	double					elapsed_time;
	t_pixel_data	*new_map;
	int				i;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	elapsed_time = (current_time.tv_sec - last_update.tv_sec) + (current_time.tv_nsec - last_update.tv_nsec) / 1e9;
	if (elapsed_time >= 1.0 / 60.0)
	{
		new_map = copy_map(image->map, image->len);
		i = 0;
		while (i < image->len)
		{
			if (delta > 0)
			{
				new_map[i].iso_x = (image->map[i].iso_x - x) * (1.1 * delta) + x;
				new_map[i].iso_y = (image->map[i].iso_y - y) * (1.1 * delta) + y;
			}
			else if (delta < 0)
			{
				new_map[i].iso_x = (image->map[i].iso_x - x) / (-1.1 * delta) + x;
				new_map[i].iso_y = (image->map[i].iso_y - y) / (-1.1 * delta) + y;
			}
			i++;
		}
		free(image->map);
		mlx_delete_image(image->mlx, image->img_iso);
		image->map = new_map;
		image->img_iso = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		//design_map(image->map, image->img, image->len, image->len_line);
		design_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
		clock_gettime(CLOCK_MONOTONIC, &last_update);
	}
}

/*Funcion que gestiona el comportamiento de scroll del mouse*/
void	ft_shook(double xdelta, double ydelta, void *param)
{
	t_image_data	*image;
	int32_t			zoom_x;
	int32_t			zoom_y;

	image = (t_image_data *) param;
	mlx_get_mouse_pos(image->mlx, &zoom_x, &zoom_y);
	if (ydelta != 0)
		ft_zoom(image, ydelta, zoom_x, zoom_y);
	else if (xdelta != 0)
		ft_printf("xdelta != 0\n");
}

/*Funcion que incializa los valores de image*/
void	start_image(t_image_data *image)
{
	image->mlx = NULL;
	image->img_iso = NULL;
	image->img_pers = NULL;
	image->map = NULL;
	image->home_map = NULL;
	image->mouse = MLX_MOUSE_NORMAL;
	image->iso_x_moved = NULL;
	image->iso_x_moved = NULL;
	image->len = 0;
	image->len_line = 0;
	image->old_x = 0;
	image->old_y = 0;
	image->is_dragging = 0;
	image->translate = 0;
	image->rotate = 0;
	image->start_rotation = 1;
	image->mod = 0;
	image->iso_pers = 0;
}

/*Funcion main de fdf*/
int	main(int argc, char **argv)
{
	t_image_data	image;
	int				fd;

	if (argc != 2)
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	start_image(&image);
	create_matrix(fd, &image);
	close(fd);
	image.mlx = mlx_init(WIDTH, HEIGHT, "My MLX42", true);
	if (image.mlx == NULL)
		exit(EXIT_FAILURE);
	image.img_iso = mlx_new_image(image.mlx, WIDTH, HEIGHT);
	if (!(image.img_iso))
	{
		mlx_terminate(image.mlx);
		exit(EXIT_FAILURE);
	}
	//design_map(image.map, image.img, image.len, image.len_line);
	design_map(&image, 0);
	image.home_map = copy_map(image.map, image.len);
	mlx_image_to_window(image.mlx, image.img_iso, 0, 0);
	mlx_key_hook(image.mlx, ft_khook, &image);
	mlx_mouse_hook(image.mlx, ft_mhook, &image);
	mlx_cursor_hook(image.mlx, ft_chook, &image);
	mlx_scroll_hook(image.mlx, ft_shook, &image);
	mlx_loop(image.mlx);
	mlx_terminate(image.mlx);
	return (EXIT_SUCCESS);
}
