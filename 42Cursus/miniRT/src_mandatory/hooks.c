/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:20:00 by rafaguti          #+#    #+#             */
/*   Updated: 2026/04/29 20:38:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef __linux__
# include <X11/Xlib.h>
# include <X11/X.h>

/**
 * @brief If the Window Manager ignores max-size hints, this function 
 * forces the window to stay within the defined framebuffer limits.
 * @param param Pointer to the main t_data runtime structure.
 * @return Always 0.
 */
static int	linux_resize_clamp(void *param)
{
	t_data				*d;
	Display				*dpy;
	Window				wid;
	XWindowAttributes	attr;
	unsigned int		size[2];

	d = (t_data *)param;
	if (!d || !d->mlx || !d->win)
		return (0);
	dpy = *(Display **)d->mlx;
	wid = *(Window *)d->win;
	XGetWindowAttributes(dpy, wid, &attr);
	size[0] = (unsigned int)attr.width;
	size[1] = (unsigned int)attr.height;
	if (size[0] > (unsigned int)WIN_W)
		size[0] = (unsigned int)WIN_W;
	if (size[1] > (unsigned int)WIN_H)
		size[1] = (unsigned int)WIN_H;
	if (size[0] != (unsigned int)attr.width
		|| size[1] != (unsigned int)attr.height)
		XResizeWindow(dpy, wid, size[0], size[1]);
	return (0);
}

#endif

/**
 * @brief Handle window close event and perform clean shutdown.
 * @param param Generic pointer to runtime data.
 * @return Always returns 0.
 */
int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cleanup_and_exit(data, 0);
	return (0);
}

/**
 * @brief Handle keyboard events and close on ESC key.
 * @param keycode Key code provided by MLX.
 * @param param Generic pointer to runtime data.
 * @return 0 if no close action was triggered.
 */
int	key_press(int keycode, void *param)
{
	if (keycode == 65307)
		return (close_window(param));
	return (0);
}

/**
 * @brief Repaint the MLX image after expose or resize (avoid black window).
 * @param param Pointer to runtime data.
 * @return Always 0.
 */
int	expose_redraw(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data && data->img.img && data->mlx && data->win)
		present_image(data);
	return (0);
}

/**
 * @brief Register keyboard, close, and expose hooks.
 * @param data Pointer to the global runtime data.
 * @return None.
 */
void	init_hooks(t_data *data)
{
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_expose_hook(data->win, expose_redraw, data);
	mlx_hook(data->win, ConfigureNotify, StructureNotifyMask,
		linux_resize_clamp, data);
}
