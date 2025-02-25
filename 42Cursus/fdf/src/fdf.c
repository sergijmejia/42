/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:15:34 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/25 19:54:54 by smejia-a         ###   ########.fr       */
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

/*Funcion para calcular las proyecciones isometricas de un cuadrado*/
void	iso_matrix_square(t_pixel_data *map_points, int len)
{
	int	x;
	int	y;
	int	z;
	int	i;

	i = 0;
	while (i < len)
	{
		x = map_points[i].x;
		y = map_points[i].y;
		z = map_points[i].z;
		map_points[i].iso_x = (int) ((x - y) * cos(M_PI / 6));
		map_points[i].iso_y = (int) (z + (x + y) * sin(M_PI / 6));
		i++;
	}
}

/*Funcion para encontrar el valor maximo de un array de flat*/
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
float   ft_min_float(float *iso, int len)
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

/*Funcion para calcular las proyecciones isometricas de una matriz de puntos*/
void	iso_matrix(t_pixel_data *map_points, int len)
{
	int	x;
	int	y;
	int	z;
	int	i;
	float	max_x;
	float	min_x;
	float	max_y;
	float	min_y;
	float	*iso_x;
	float	*iso_y;
	float	prop_x;
	float	prop_y;

	i = 0;
	iso_x = (float *) malloc (sizeof(float) * len);
	iso_y = (float *) malloc (sizeof(float) * len);
	while (i < len)
	{
		x = map_points[i].x;
		y = map_points[i].y;
		z = map_points[i].z;
		iso_x[i] = (x - y) * cos(M_PI / 6);
		iso_y[i] = (-1) * (z / 12.0) + (x + y) * sin(M_PI / 6);
		printf("El punto %d (%d, %d) tiene coordenadas isometricas (%f, %f) y tiene altura z = %d\n", i, x, y, iso_x[i], iso_y[i], z);
		i++;
	}
	max_x = ft_max_float(iso_x, len);
	min_x = ft_min_float(iso_x, len);
	max_y = ft_max_float(iso_y, len);
	min_y = ft_min_float(iso_y, len);

	i = 0;
	prop_x = 0;
	prop_y = 0;
	if ((max_x - min_x) / WIDTH > (max_y - min_y) / HEIGHT)
		prop_x = 1;
	else
		prop_y = 1;
	printf("Los valores min y maximo son min_x = %f, min_y = %f, max_x = %f, max_y = %f\n", min_x, min_y, max_x, max_y);
	while (i < len)
	{
		if (prop_x)
		{		
			map_points[i].iso_x = (int) (((iso_x[i] - min_x) / (max_x - min_x)) * (19.0 / 20.0) * WIDTH);
			map_points[i].iso_y = (int) (((iso_y[i] - min_y) / (max_x - min_x)) * (19.0 / 20.0) * WIDTH);
		}
		if (prop_y)
		{
			map_points[i].iso_y = (int) (((iso_y[i] - min_y) / (max_y - min_y)) * (19.0 / 20.0) * HEIGHT);
			map_points[i].iso_x = (int) (((iso_x[i] - min_x) / (max_y - min_y)) * (19.0 / 20.0) * HEIGHT);
		}
		printf("El punto (%d, %d) tiene coordenadas isometricas (%d, %d)\n", map_points[i].x, map_points[i].y, map_points[i].iso_x, map_points[i].iso_y);
		i++;
	}
}

/*Funcion para modificar la longitud del array de coordendas*/
t_pixel_data	*realloc_map(t_pixel_data *map_points, int old_len, int new_len)
{
	t_pixel_data	*new_map;
	int	i;

	new_map	= (t_pixel_data *) malloc (sizeof(t_pixel_data) * new_len);
	i = 0;
	while (i < old_len)
	{
		new_map[i] = map_points[i];
		i++;
	}
	free(map_points);
	return (new_map);
}

/*Funcion para copiar la memoria de un mapa a otro
void	map_move(t_pixel_data **map_points, t_pixel_data **tmp_map, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_points[i] != NULL)
		i++;
	while (j < len)
	{
		map_points[i + j] = tmp_map[j];
		j++;	
	}
}*/

/*Funcion para crear el array con las coordenadas de los puntos del mapa*/
t_pixel_data	*create_matrix(int fd, int *len_map, int *len_line)
{
	char			*line;
	char			**split_line;
	t_pixel_data	*map_points;
	int				len;
	int				old_len;
	int				i;
	int				j;

	map_points = NULL;
	*len_map = 0;
	old_len = 0;
	*len_line = 0;
	j = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		split_line = ft_split(line, ' ');
		if (!split_line)
			return (NULL);
		len = 0;
		while (split_line[len] != NULL)
			len++;
		*len_map = len + old_len;
		map_points = realloc_map(map_points, old_len, *len_map);
		i = 0;
		while (i < len)
		{
			map_points[old_len + i].x = i;
			map_points[old_len + i].y = j;
			map_points[old_len + i].z = ft_atoi(split_line[i]);
			map_points[old_len + i].net_x = 0;
			map_points[old_len + i].net_y = 0;
			if (i > 0)
				map_points[old_len + i].net_x = 1;
			if (i < *len_line)
				map_points[old_len + i].net_y = 1;
			i++;
		}
		free(line);
		ft_clean_split(split_line);
		line = get_next_line(fd);
		old_len = *len_map;
		*len_line = len;
		j++;
	}
	iso_matrix(map_points, *len_map);
	return (map_points);
}

/*Funcion para unir 2 puntos
void	join_points(mlx_image_t	*img)
{

}*/

/*Funcion para pintar una matriz de pixeles
void	design_matrix(mlx_image_t *img, t_pixel_data **map)
{

}*/

/*Funcion para dibujar un cuadrado de color rojo
void	design_square(mlx_image_t *img)
{
	int	x;
	int	y;
	int	index;
	t_pixel_data	*map_points;
	int	len;
	int	i;
	int	iso_x;
	int	iso_y;

	len = 100 * 50;
	map_points = (t_pixel_data *) malloc (sizeof(t_pixel_data) * len);
	i = 0;
	y = 50;
	while (y < 150)
	{
		x = 75;
		while (x < 125)
		{
			map_points[i].x = x;
			map_points[i].y = y;
			map_points[i].z = 0;
			x++;
			i++;
		}
		y++;
	}
	iso_matrix_square(map_points, len);
	i = 0;
	while (i < len)
	{
		iso_x = (int) map_points[i].iso_x + img->width / 2;
		iso_y = (int) map_points[i].iso_y + img->height / 2;
		index = (iso_y * img->width + iso_x) * 4;
		if (index >= 0)
		{
			img->pixels[index] = 255; //rojo
			img->pixels[index + 1] = 0; //verde
			img->pixels[index + 2] = 0; //azul
			img->pixels[index + 3] = 255; //alpha
		}
		i++;
	}
}*/

/*Algoritmo de Bresenham
void	draw_line(mlx_image_t *img, t_pixel_data point0, t_pixel_data point1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	index;
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	i;

	x0 = point0.iso_x; //+ img->width / 2;
	x1 = point1.iso_x; //+ img->width / 2;
	y0 = point0.iso_y; //+ img->height / 2;
	y1 = point1.iso_y; //+ img->height / 2;
	ft_printf("Las coordenadas del punto 0 son (%d, %d)\n", x0, y0);
	ft_printf("Las coordenadas del punto 1 son (%d, %d)\n", x1, y1);
	dx = ft_abs(x1 - x0);
	dy = ft_abs(y1 - y0);
	if (x1 > x0)
		sx = 1;
	else
		sx = -1;
	if (y1 > y0)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	i = 0;
	while (1)
	{
		if ((x0 - sx == x1) || (y0 - sy == y1))
			break ;
		ft_printf("Bucle numero %d\n", i);
		index = (y0 * img->width + x0) * 4;
		if ((index >= 0) && (index < (int) (img->width * img->height * 4)))
		{
			img->pixels[index] = 255;		// Rojo
			img->pixels[index + 1] = 255;		// Verde
			img->pixels[index + 2] = 255;		// Azul
			img->pixels[index + 3] = 255;		//Alpha
		}
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)  //avanza en x
		{
			err = err - dy;
			x0 = x0 + sx;
		}
		if (e2 <= dx) //avanza en y
		{
			err = err + dx;
			y0 = y0 + sy;
		}
		ft_printf("x0 = %d, x1 = %d, y0 = %d, y1 = %d, dx = %d, dy = %d, err = %d, e2 = %d\n", x0, x1, y0, y1, dx, dy, err, e2);
		i++;
	}
}*/

/*Algoritmo de Bresenham*/
void	draw_line(mlx_image_t *img, t_pixel_data point0, t_pixel_data point1)
{
	int	dx;
	int	dy;
	int	sxi;
	int	syi;
	int	index;
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	i;
	int	syr;
	int	sxr;
	int	avr;
	int	av;
	int	avi;

	x0 = point0.iso_x; //+ img->width / 2;
	x1 = point1.iso_x; //+ img->width / 2;
	y0 = point0.iso_y; //+ img->height / 2;
	y1 = point1.iso_y; //+ img->height / 2;
	ft_printf("Las coordenadas del punto 0 son (%d, %d)\n", x0, y0);
	ft_printf("Las coordenadas del punto 1 son (%d, %d)\n", x1, y1);
	dx = x1 - x0;
	dy = y1 - y0;
	if (dx >= 0)
		sxi = 1;
	else
	{
		dx = (-1) * dx;
		sxi = -1;
	}
	if (dy >= 0)
		syi = 1;
	else
	{
		dy = (-1) * dy;
		syi = -1;
	}
	if (dx >= dy)
	{
		syr = 0;
		sxr = sxi;
	}
	else
	{
		sxr = 0;
		syr = syi;
		i = dx;
		dx = dy;
		dy = i;
	}
	avr = 2 * dy;
	av = avr - dx;
	avi = av - dx;
	i = 0;
	ft_printf("x1 = %d, y1 = %d, sxi = %d, syi = %d, sxr = %d, syr = %d, avr = %d, avi = %d\n", x1, y1, sxi, syi, sxr, syr, avr, avi);
	while (x0 != x1 || y0 != y1)
	{
		//ft_printf("Bucle numero %d\n", i);
		index = (y0 * img->width + x0) * 4;
		if ((index >= 0) && (index < (int) (img->width * img->height * 4)))
		{
			img->pixels[index] = 255;		// Rojo
			img->pixels[index + 1] = 255;		// Verde
			img->pixels[index + 2] = 255;		// Azul
			img->pixels[index + 3] = 255;		//Alpha
		}
		if (av >= 0)
		{
			x0 = x0 + sxi;
			y0 = y0 + syi;
			av = av + avi;
		}
		else
		{
			x0 = x0 + sxr;
			y0 = y0 + syr;
			av = av + avr;
		}
		//ft_printf("x0 = %d, x1 = %d, y0 = %d, y1 = %d, av = %d\n", x0, x1, y0, y1, av);
		//i++;
	}
}

/*Funcion para dibujar el perimetro de un cuadrado rojo*/
void	perimeter_square(mlx_image_t *img)
{
	int	len;
	t_pixel_data	*map_points;

	len = 4;
	map_points = (t_pixel_data *) malloc (sizeof(t_pixel_data) * len);
	map_points[0].x = 50;
	map_points[0].y = 50;
	map_points[0].z = 0;
	map_points[1].x = 50;
	map_points[1].y = 150;
	map_points[1].z = 0;
	map_points[2].x = 150;
	map_points[2].y = 150;
	map_points[2].z = 0;
	map_points[3].x = 150;
	map_points[3].y = 50;
	map_points[3].z = 0;
	iso_matrix_square(map_points, len);
	draw_line(img, map_points[0], map_points[1]);
	draw_line(img, map_points[1], map_points[2]);
	draw_line(img, map_points[2], map_points[3]);
	draw_line(img, map_points[3], map_points[0]);
}

/*Funcion para dibujar el mapa de la matriz*/
void	design_map(t_pixel_data *map_points, mlx_image_t *img, int len, int len_line)
{
	int	i;

	ft_printf("len = %d\n", len);
	i = 1;
	while (i < len)
	{
		if (map_points[i].net_x)
		{
			ft_printf("Dibujo linea x numero %d\n", i);
			draw_line(img, map_points[i - 1], map_points[i]);
		}
		if (map_points[i].net_y)
		{
			ft_printf("Dibujo linea y numero %d\n");
			draw_line(img, map_points[i - len_line], map_points[i]);
		}
		i++;
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
	t_pixel_data	*pixel;
	int	len;
	int	len_line;
	int	fd;

	if (argc != 2)
		return (EXIT_FAILURE);
	//ft_printf("%s\n", argv[1]);
	fd = open(argv[1], O_RDONLY);
	pixel = NULL;
	ft_printf("Abre el archivo con nombre %s\n", argv[1]);
	pixel = create_matrix(fd, &len, &len_line);
	if (pixel)
		ft_printf("len = %d\n", len);
	image.mlx = mlx_init(WIDTH, HEIGHT, "My MLX42", true);
	if (image.mlx == NULL)
		exit(EXIT_FAILURE);
	image.img = mlx_new_image(image.mlx, WIDTH, HEIGHT);
	if (!(image.img))
	{
		mlx_terminate(image.mlx);
		exit(EXIT_FAILURE);
	}
	//perimeter_square(image.img);
	design_map(pixel, image.img, len, len_line);
	//design_square(image.img);
	//mlx_put_pixel(img, 100, 100, 0xFFFF0000);
	//mlx_put_pixel(img, 110, 110, 0xFF00FF00);
	//mlx_put_pixel(img, 120, 120, 0xFF0000FF);
	mlx_image_to_window(image.mlx, image.img, 100, 100);
	mlx_key_hook(image.mlx, ft_key_hook, &image);
	mlx_loop(image.mlx);
	mlx_terminate(image.mlx); //libera memoria antes de salir
	close(fd);
	return (EXIT_SUCCESS);
}
