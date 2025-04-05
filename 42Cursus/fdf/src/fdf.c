/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:15:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/04 12:14:46 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que incializa los valores de image*/
static void	start_image(t_image_data *image)
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
	image->rgb = 0;
}

/*Funcion que lee los datos y genera el mapa*/
static void	create_map(t_image_data *image, char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("Fail open fd");
		exit(EXIT_FAILURE);
	}
	create_matrix(fd, image);
	close(fd);
	image->mlx = mlx_init(WIDTH, HEIGHT, "My MLX42", true);
	if (image->mlx == NULL)
	{
		perror("Fail creating .mlx");
		end_image(image);
		exit(EXIT_FAILURE);
	}
	image->img_iso = mlx_new_image(image->mlx, WIDTH, HEIGHT);
	image->img_pers = mlx_new_image(image->mlx, WIDTH, HEIGHT);
	if (image->img_iso == NULL || image->img_pers == NULL)
	{
		end_image(image);
		mlx_terminate(image->mlx);
		exit(EXIT_FAILURE);
	}
}

/*Funcion del loop del fdf*/
static void	loop(t_image_data *image)
{
	mlx_key_hook(image->mlx, ft_khook, image);
	mlx_mouse_hook(image->mlx, ft_mhook, image);
	mlx_cursor_hook(image->mlx, ft_chook, image);
	mlx_scroll_hook(image->mlx, ft_shook, image);
	mlx_loop(image->mlx);
}

/*Funcion main de fdf*/
int	main(int argc, char **argv)
{
	t_image_data	image;

	if (argc != 2)
	{
		write(2, "Wrong number of arguments. ", 28);
		write(2, "Fdf can only handle one file at a time.\n", 41);
		exit(EXIT_FAILURE);
	}
	start_image(&image);
	create_map(&image, argv[1]);
	draw_map(&image, 0);
	image.home_map = copy_map(image.map, image.len);
	if (mlx_image_to_window(image.mlx, image.img_iso, 0, 0) == -1)
	{
		end_image(&image);
		mlx_terminate(image.mlx);
		perror("Error rendering image");
		exit(EXIT_FAILURE);
	}
	loop(&image);
	end_image(&image);
	mlx_terminate(image.mlx);
	return (EXIT_SUCCESS);
}
