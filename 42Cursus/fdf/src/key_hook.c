/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:41:57 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/31 12:13:34 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que gestiona el comportamiento de la barra espaciadora*/
static void	ft_space_key(t_image_data *image)
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

/*Funcion que gestiona el comportamiento de la letra a para cambiar de mapas*/
static void	ft_a_key(action_t act, t_image_data *image)
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
