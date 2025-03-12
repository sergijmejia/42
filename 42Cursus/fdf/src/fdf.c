/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:15:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/12 19:05:01 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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
float	ft_max_float(float *iso, int len)
{
	float	max;
	int		i;

	max = iso[0];
	i = 0;
	while (i < len)
	{
		if (iso[i] > max)
			max = iso[i];
		i++;
	}
	return (max);
}

/*Funcion para encontrar el valor minimo de un array de flat*/
float	ft_min_float(float *iso, int len)
{
	float	min;
	int		i;

	min = iso[0];
	i = 0;
	while (i < len)
	{
		if (iso[i] < min)
			min = iso[i];
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
void	transf_iso_matrix_prop_x(t_pixel_data *map_points, t_isometric_data data, float *iso_x, float *iso_y, int len)
{
	int		i;
	float	dx;
	float	sy;
	float	x;
	float	y;

	i = 0;
	dx = data.max_x - data.min_x;
	sy = data.max_y + data.min_y;
	while (i < len)
	{
		x = 1 + 38.0 * (iso_x[i] - data.min_x) / dx;
		y = (19.0 * WIDTH) * (2 * iso_y[i] - sy) / (40.0 * dx);
		map_points[i].iso_x = (int)(WIDTH * x / 40.0);
		map_points[i].iso_y = (int)(y + (HEIGHT / 2));
		i++;
	}
}

/*Funcion que transforma las proyecciones isometricas con proporcion en eje y*/
void	transf_iso_matrix_prop_y(t_pixel_data *map_points, t_isometric_data data, float *iso_x, float *iso_y, int len)
{
	int		i;
	float	dy;
	float	sx;
	float	x;
	float	y;

	i = 0;
	dy = data.max_y - data.min_y;
	sx = data.max_x + data.min_x;
	while (i < len)
	{
		x = (19.0 * HEIGHT) * (2 * iso_x[i] - sx) / (40.0 * dy);
		y = 1 + 38.0 * (iso_y[i] - data.min_y) / dy;
		map_points[i].iso_y = (int)(HEIGHT * y / 40.0);
		map_points[i].iso_x = (int)(x + (WIDTH / 2));
		i++;
	}
}

/*Funcion para calcular las proyecciones isometricas de una matriz de puntos*/
void	iso_matrix(t_image_data *image)
{
	t_isometric_data	data;
	float				*iso_x;
	float				*iso_y;
	float				prop_x;
	float				prop_y;

	iso_x = proj_iso_x(image->map, image->len);
	iso_y = proj_iso_y(image->map, image->len);
	data.max_x = ft_max_float(iso_x, image->len);
	data.min_x = ft_min_float(iso_x, image->len);
	data.max_y = ft_max_float(iso_y, image->len);
	data.min_y = ft_min_float(iso_y, image->len);
	prop_x = (data.max_x - data.min_x) / WIDTH;
	prop_y = (data.max_y - data.min_y) / HEIGHT;
	if (prop_x > prop_y)
		transf_iso_matrix_prop_x(image->map, data, iso_x, iso_y, image->len);
	else
		transf_iso_matrix_prop_y(image->map, data, iso_x, iso_y, image->len);
	free(iso_x);
	free(iso_y);
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
	int	i;
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

/*Funcion para crear el array con las coordenadas de los puntos del mapa*/
void	create_matrix(int fd, t_image_data *image)
{
	char			*line;
	char			**split_line;
	int				len;
	int				old_len;
	int				i;
	int				j;

	old_len = 0;
	j = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		split_line = ft_split(line, ' ');
		if (!split_line)
			return ;
		len = 0;
		while (split_line[len] != NULL)
			len++;
		image->len = len + old_len;
		image->map = realloc_map(image, old_len);
		i = 0;
		while (i < len)
		{
			image->map[old_len + i].x = i;
			image->map[old_len + i].y = j;
			image->map[old_len + i].z = ft_atoi(split_line[i]);
			image->map[old_len + i].net_x = 0;
			image->map[old_len + i].net_y = 0;
			if (i > 0)
				image->map[old_len + i].net_x = 1;
			if (i < image->len_line)
				image->map[old_len + i].net_y = 1;
			i++;
		}
		free(line);
		ft_clean_split(split_line);
		line = get_next_line(fd);
		old_len = image->len;
		image->len_line = len;
		j++;
	}
	iso_matrix(image);
}

/*Funcion para dibujar el mapa de la matriz*/
void	design_map(t_pixel_data *map_points, mlx_image_t *img, int len, int len_line)
{
	int	i;

	i = 1;
	while (i < len)
	{
		if (map_points[i].net_x)
			draw_line(img, map_points[i - 1], map_points[i]);
		if (map_points[i].net_y)
			draw_line(img, map_points[i - len_line], map_points[i]);
		i++;
	}

}

/*Funcion que gestiona el comportamiento de la barra espaciadora*/
void	ft_space_key(t_image_data *image)
{
	free(image->map);
	mlx_delete_image(image->mlx, image->img);
	image->map = copy_map(image->home_map, image->len);
	image->img = mlx_new_image(image->mlx, WIDTH, HEIGHT);
	design_map(image->map, image->img, image->len, image->len_line);
	mlx_image_to_window(image->mlx, image->img, 0, 0);
}

/*Funcion para realizar la rotacion respecto al movimiento del cursor*/
void	ft_image_rotation(t_image_data *image, double xpos, double ypos)
{
	t_pixel_data	*new_map;
	int				i;
	static int32_t	x0;
	static int32_t	y0;
	double			x_rel;
	double			y_rel;
	double			x_new;
	double			y_new;
	double			theta0;
	static double	theta0_mod = 0.0;
	double			theta1;
	double			theta;


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
	new_map = copy_map(image->map, image->len);
	i = 0;
	//theta0 = atan2(image->old_y - y0, image->old_x - x0);
	theta1 = atan2(ypos - y0, xpos - x0);
	theta = theta1 - theta0;
	if (image->mod == 1)
		theta0_mod = theta1;
	image->old_x = (int32_t) xpos;
	image->old_y = (int32_t) ypos;
	while (i < image->len)
	{
		x_rel = image->map[i].iso_x - x0;
		y_rel = image->map[i].iso_y - y0;
		x_new = x_rel * cos(theta) - y_rel * sin(theta);
		y_new = x_rel * sin(theta) + y_rel * cos(theta);
		new_map[i].iso_x = x_new + x0;
		new_map[i].iso_y = y_new + y0;
		i++;
	}
	free(image->map);
	mlx_delete_image(image->mlx, image->img);
	image->map = new_map;
	image->img = mlx_new_image(image->mlx, WIDTH, HEIGHT);
	design_map(image->map, image->img, image->len, image->len_line);
	mlx_image_to_window(image->mlx, image->img, 0, 0);
}

/*Funcion para realizar la traslacion respecto al movimiento del cursor*/
void	ft_image_traslation(t_image_data *image, double xpos, double ypos)
{
	t_pixel_data	*new_map;
	double			dx;
	double			dy;
	int				i;

	new_map = copy_map(image->map, image->len);
	dx = xpos - image->old_x;
	dy = ypos - image->old_y;
	image->old_x = (int32_t) xpos;
	image->old_y = (int32_t) ypos;
	i = 0;
	while (i < image->len)
	{
		new_map[i].iso_x = image->map[i].iso_x + dx;
		new_map[i].iso_y  = image->map[i].iso_y + dy;
		i++;
	}
	free(image->map);
	mlx_delete_image(image->mlx, image->img);
	image->map = new_map;
	image->img = mlx_new_image(image->mlx, WIDTH, HEIGHT);
	design_map(image->map, image->img, image->len, image->len_line);
	mlx_image_to_window(image->mlx, image->img, 0, 0);
}


/*Funcion que gestiona el comportamiento cuando el cursor se mueve*/
void	ft_chook(double xpos, double ypos, void *par)
{
	t_image_data *image; 

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
void    ft_mouse_right(action_t act, modifier_key_t mod, t_image_data *image)
{
	int32_t			initial_x;
	int32_t			initial_y;

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
}

/*Funcion que gestiona el comportamiento de scroll del mouse
void	ft_shook(double xdelta, double ydelta, void* param)
{
	t_image_data	*image;
	dou

	image = (t_image_data *) param;
}*/

/*Funcion que incializa los valores de image*/
void	start_image(t_image_data *image)
{
	image->mlx = NULL;
	image->img = NULL;
	image->map = NULL;
	image->home_map = NULL;
	image->mouse = MLX_MOUSE_NORMAL;
	image->len = 0;
	image->len_line = 0;
	image->old_x = 0;
	image->old_y = 0;
	image->is_dragging = 0;
	image->translate = 0;
	image->rotate = 0;
	image->start_rotation = 1;
	image->mod = 0;
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
	image.img = mlx_new_image(image.mlx, WIDTH, HEIGHT);
	if (!(image.img))
	{
		mlx_terminate(image.mlx);
		exit(EXIT_FAILURE);
	}
	design_map(image.map, image.img, image.len, image.len_line);
	image.home_map = copy_map(image.map, image.len);
	mlx_image_to_window(image.mlx, image.img, 0, 0);
	mlx_key_hook(image.mlx, ft_khook, &image);
	mlx_mouse_hook(image.mlx, ft_mhook, &image);
	mlx_cursor_hook(image.mlx, ft_chook, &image);
	//mlx_scroll_hook(image.mlx, ft_shook, &image);
	mlx_loop(image.mlx);
	mlx_terminate(image.mlx);
	return (EXIT_SUCCESS);
}
