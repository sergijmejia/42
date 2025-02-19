/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:15:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/19 16:27:07 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion de libearacion de memoria de la matriz*/
t_pixel_data	*ft_clean_matrix(t_pixel_data **pixel, int height)
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

/*Funcion para crear la matriz con las coordenadas de los puntos del mapa
t_pixel_data	**create_matrix(int fd)
{

}*/

/*Funcion para dibujar un cuadrado de color rojo*/
void	design_square(mlx_image_t *img)
{
	int	x;
	int	y;
	int	index;

	y = 50;
	while (y < 150)
	{
		x = 75;
		while (x < 125)
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

/*Funcion de transformacion
void	transform_design(mlx_image_t *img)
{
	mlx_image_t	tmp;

	index = 
}*/

/*Funcion que gestiona el comportamiento de ciertas teclas del teclado*/
void	ft_key_hook(mlx_key_data_t key_hook, void *param)
{
	t_image_data	*image;

	image = (t_image_data*)param;
	if (key_hook.key == MLX_KEY_ESCAPE)
		mlx_close_window(image->mlx);
	if (key_hook.key == MLX_KEY_UP)
		image->img->instances[0].y = image->img->instances[0].y - 10;
	if (key_hook.key == MLX_KEY_DOWN)
		image->img->instances[0].y = image->img->instances[0].y + 10;
	if (key_hook.key == MLX_KEY_LEFT)
		image->img->instances[0].x = image->img->instances[0].x - 10;
	if (key_hook.key == MLX_KEY_RIGHT)
		image->img->instances[0].x = image->img->instances[0].x + 10;
}

/*Funcion main de fdf*/
int	main(int argc, char **argv)
{
	t_image_data	image;
	//t_pixel_data	**pixel;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_printf("%s\n", argv[1]);
	//fd = open(argv[1], O_RDONLY);
	//pixel = create_matrix(fd);
	image.mlx = mlx_init(WIDTH, HEIGHT, "My MLX42", true);
	if (image.mlx == NULL)
		exit(EXIT_FAILURE);
	image.img = mlx_new_image(image.mlx, 200, 200);
	if (!(image.img))
	{
		mlx_terminate(image.mlx);
		exit(EXIT_FAILURE);
	}
	design_square(image.img);
	//mlx_put_pixel(img, 100, 100, 0xFFFF0000);
	//mlx_put_pixel(img, 110, 110, 0xFF00FF00);
	//mlx_put_pixel(img, 120, 120, 0xFF0000FF);
	mlx_image_to_window(image.mlx, image.img, 100, 100);
	mlx_key_hook(image.mlx, ft_key_hook, &image);
	mlx_loop(image.mlx);
	mlx_terminate(image.mlx); //libera memoria antes de salir
	return (EXIT_SUCCESS);
}
