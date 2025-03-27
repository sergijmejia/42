/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:15:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/27 16:42:47 by smejia-a         ###   ########.fr       */
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

/*Funcion que gestiona el comportamiento de la barra espaciadora*/
void	ft_space_key(t_image_data *image)
{	
	free(image->map);
	if (image->iso_pers == 0)
	{
		mlx_delete_image(image->mlx, image->img_iso);
		image->map = copy_map(image->home_map, image->len);
		image->img_iso = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		draw_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
	}
	else
	{
		mlx_delete_image(image->mlx, image->img_pers);
		image->map = copy_map(image->home_map, image->len);
		image->img_pers = mlx_new_image(image->mlx, WIDTH, HEIGHT);
		draw_map(image, 0);
		mlx_image_to_window(image->mlx, image->img_pers, 0, 0);
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
void	ft_a_key(action_t act, t_image_data *image)
{
	if (act == MLX_PRESS)
	{
		if (image->iso_pers == 0)
		{
			clear_image(image);
			image->iso_pers = 1;
			draw_map(image, 0);
			mlx_image_to_window(image->mlx, image->img_pers, 0, 0);
		}
		else
		{
			clear_image(image);
			image->iso_pers = 0;
			draw_map(image, 0);
			mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
		}
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
		ft_a_key(key_hook.action, image);
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
		if (image->iso_pers)
		{
			while (i < image->len)
			{
				if (delta > 0)
				{
					new_map[i].pers_x = (image->map[i].pers_x - x) * (1.1 * delta) + x;
					new_map[i].pers_y = (image->map[i].pers_y - y) * (1.1 * delta) + y;
				}
				else if (delta < 0)
				{
					new_map[i].pers_x = (image->map[i].pers_x - x) / (-1.1 * delta) + x;
					new_map[i].pers_y = (image->map[i].pers_y - y) / (-1.1 * delta) + y;
				}
				i++;
			}
			free(image->map);
			mlx_delete_image(image->mlx, image->img_pers);
			image->map = new_map;
			image->img_pers = mlx_new_image(image->mlx, WIDTH, HEIGHT);
			draw_map(image, 0);
			mlx_image_to_window(image->mlx, image->img_pers, 0, 0);
		}
		else
		{
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
			draw_map(image, 0);
			mlx_image_to_window(image->mlx, image->img_iso, 0, 0);
		}
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
	image.img_pers = mlx_new_image(image.mlx, WIDTH, HEIGHT);
	if (!(image.img_iso))
	{
		mlx_terminate(image.mlx);
		exit(EXIT_FAILURE);
	}
	draw_map(&image, 0);
	image.home_map = copy_map(image.map, image.len);
	mlx_image_to_window(image.mlx, image.img_iso, 0, 0);
	mlx_key_hook(image.mlx, ft_khook, &image);
	mlx_mouse_hook(image.mlx, ft_mhook, &image);
	mlx_cursor_hook(image.mlx, ft_chook, &image);
	mlx_scroll_hook(image.mlx, ft_shook, &image);
	mlx_loop(image.mlx);
	free(image.home_map);
	mlx_terminate(image.mlx);
	return (EXIT_SUCCESS);
}
