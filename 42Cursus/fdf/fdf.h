/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:16:24 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/19 11:38:03 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <./MLX42/include//MLX42/MLX42.h>
# include "./libft/libft.h"

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
}	t_pixel_data;

typedef struct s_image_data
{
	mlx_t	*mlx;
	mlx_image_t	*img;
}	t_image_data;

# ifndef WIDTH
#  define WIDTH 3840
# endif

# ifndef HEIGHT
#  define HEIGHT 2160
# endif

#endif
