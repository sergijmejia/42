/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:16:24 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/25 18:53:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "./libft/libft.h"
# include <math.h>
# include <time.h>

/*Estructura de las dimensiones de la ventana*/
typedef struct s_window
{
	int	width;
	int	height;
}	t_window;

/*Estructura de la informacion de cada nodo del mapa*/
typedef struct s_pixel_data
{
	int				x;
	int				y;
	int				z;
	int				net_x;
	int				net_y;
	double			iso_x;
	double			iso_y;
	double			pers_x;
	double			pers_y;
	//char			color[9];
	int				r;
	int				g;
	int				b;
}	t_pixel_data;

/*Estructura que contiene la informacion de la imagen*/
typedef struct s_image_data
{
	mlx_t			*mlx;
	mlx_image_t		*img_iso;
	mlx_image_t		*img_pers;
	t_pixel_data	*map;
	t_pixel_data	*home_map;
	mouse_mode_t	mouse;
	int				*iso_x_moved;
	int				*iso_y_moved;
	int				len;
	int				len_line;
	int32_t			old_x;
	int32_t			old_y;
	int				is_dragging;
	int				translate;
	int				rotate;
	int				start_rotation;
	int				mod;
	int				iso_pers;
}	t_image_data;

/*Estructura que contiene los valores maximo y minimo de la proyeccion
en mapa*/
typedef struct s_proj_data
{
	float	min_iso_x;
	float	max_iso_x;
	float	min_iso_y;
	float	max_iso_y;
	float	min_pers_x;
	float	max_pers_x;
	float	min_pers_y;
	float	max_pers_y;
}	t_proj_data;

/*Estructura de los datos de la linea dibujada con el algoritmo de Bresenham*/
typedef struct s_line_data
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		sx_st;
	int		sx_in;
	int		sy_st;
	int		sy_in;
	int		dx;
	int		dy;
	int		adv_st;
	int		adv_in;
	int		adv;
	int		r0;
	int		g0;
	int		b0;
	int		r1;
	int		g1;
	int		b1;
	double	color_ratio;
}	t_line_data;

# ifndef WIDTH
#  define WIDTH 3840
# endif

# ifndef HEIGHT
#  define HEIGHT 1882
# endif

/*Algoritmo de Bresenham para dibijar una linea entre dos puntos*/
void	draw_line(t_image_data *image, t_pixel_data point0, t_pixel_data point1, int clear);

/*Prueba*/
int	get_color(char const *s, char *color);
#endif
