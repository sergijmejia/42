/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:15:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/18 17:00:43 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion de libearacion de memoria de la matriz*/
t_pixel_data	*ft_clean_matrix(t_pixel_data **pixel, int width, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(pixel[i]);
		pixel[i] = NULL;
		i++;
	}
	free(pixel);
	pixel = NULL;
	return (NULL);
}

t_pixel_data	**create_matrix(int fd)
{

}

void	design_square(mlx_image_t *img)
{
	int	x;
	int	y;
	int	index;

	y = 50;
	while (y < 150)
	{
		x = 50;
		while (x < 150)
		{
			index = (y * img->width + x) * 4;
			img->pixels[index] = 255; //rojo
			img->pixels[index + 1] = 0; //verde
			img->pixels[index + 2] = 0; //azul
			img->pixels[index + 3] = 255; //alpha
			x++;
		}
		y++;
	}
}

void	ft_key_hook(mlx_key_data_t key_hook, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t*)param;
	if (key_hook.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(mlx);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	mlx_image_t	*img;
	t_pixel_data	**pixel;

	if (argc != 2)
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	pixel = create_matrix(fd);
	mlx = mlx_init(WIDTH, HEIGHT, "My MLX42", true);
	if (mlx == NULL)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, 200, 200);
	if (!img)
	{
		mlx_terminate(mlx);
		exit(EXIT_FAILURE);
	}
	design_square(img);
	mlx_image_to_window(mlx, img, 100, 100);
	mlx_key_hook(mlx, ft_key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx); //libera memoria antes de salir
	return (EXIT_SUCCESS);
}
