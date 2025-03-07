/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:16:24 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/07 17:29:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <./MLX42/include//MLX42/MLX42.h>
# include "./libft/libft.h"
# include <math.h>

typedef struct s_window
{
	int	width;
	int	height;
}	t_window;

typedef struct s_pixel_data
{
	int	x;
	int	y;
	int	z;
	int	net_x;
	int	net_y;
	int	iso_x;
	int	iso_y;
}	t_pixel_data;

typedef struct s_image_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_pixel_data	*map;
	int				len;
	int				len_line;
	int32_t			old_x;
	int32_t			old_y;
	int				is_dragging;
}	t_image_data;

typedef struct s_isometric_data
{
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
}	t_isometric_data;

typedef struct	s_line_data
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	sx_st;
	int	sx_in;
	int	sy_st;
	int	sy_in;
	int	dx;
	int	dy;
	int	adv_st;
	int	adv_in;
	int	adv;
}	t_line_data;

# ifndef WIDTH
#  define WIDTH 3840
# endif

# ifndef HEIGHT
#  define HEIGHT 1882
# endif

/*Algoritmo de Bresenham para dibijar una linea entre dos puntos*/
void	draw_line(mlx_image_t *img, t_pixel_data point0, t_pixel_data point1);

#endif
