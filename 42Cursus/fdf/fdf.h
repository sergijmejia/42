/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:16:24 by smejia-a          #+#    #+#             */
/*   Updated: 2025/02/18 16:39:04 by smejia-a         ###   ########.fr       */
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

# ifndef WIDTH
#  define WIDTH 3840
# endif

# ifndef HEIGHT
#  define HEIGHT 2160
# endif

#endif
