/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:31:12 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/31 12:14:44 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fdf_utils.h>

/*Funcion que gestiona el comportamiento del boton izquierdo del mouse*/
static void	mouse_left(action_t act, modifier_key_t mod, t_image_data *image)
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
static void	mouse_right(action_t act, modifier_key_t mod, t_image_data *image)
{
	int32_t	initial_xy[2];

	if (act == MLX_PRESS)
	{
		if (mod == MLX_SHIFT)
			image->mod = 1;
		else
			image->mod = 0;
		mlx_get_mouse_pos(image->mlx, &initial_xy[0], &initial_xy[1]);
		image->old_x = initial_xy[0];
		image->old_y = initial_xy[1];
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

/*Funcion que gestiona el comportamiento de teclas del mouse*/
void	ft_mhook(mouse_key_t key, action_t act, modifier_key_t mod, void *par)
{
	t_image_data	*image;

	image = (t_image_data *) par;
	if (key == MLX_MOUSE_BUTTON_LEFT)
		mouse_left(act, mod, image);
	if (key == MLX_MOUSE_BUTTON_RIGHT)
		mouse_right(act, mod, image);
}
