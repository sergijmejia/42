/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:20:00 by rafaguti          #+#    #+#             */
/*   Updated: 2026/04/29 20:38:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef __linux__
# include <string.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>

/**
 * @brief Limit maximum window size to the fixed render resolution (Linux/X11).
 * @param mlx Pointer returned by mlx_init (internal layout: Display* is first).
 * @param mlx_win Pointer returned by mlx_new_window (internal layout: Window first).
 * @param w Maximum width (same as framebuffer).
 * @param h Maximum height (same as framebuffer).
 * @return None.
 *
 * Prevents enlarging past the image size (avoids empty black margins). Shrinking
 * may still be allowed depending on the window manager.
 */
static void	x11_cap_window_max(void *mlx, void *mlx_win, int w, int h)
{
	Display			*dpy;
	Window			wid;
	XSizeHints		hints;
	long			supplied;

	dpy = *(Display **)mlx;
	wid = *(Window *)mlx_win;
	memset(&hints, 0, sizeof(hints));
	supplied = 0;
	XGetWMNormalHints(dpy, wid, &hints, &supplied);
	hints.flags |= (long)PMaxSize;
	hints.max_width = w;
	hints.max_height = h;
	XSetWMNormalHints(dpy, wid, &hints);
	XFlush(dpy);
}
#endif

/**
 * @brief Initialize MLX context (no window yet; allows render before map).
 * @param data Pointer to the global runtime data.
 * @return None.
 */
void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
}

/**
 * @brief Create the application window after the image buffer is ready.
 * @param data Pointer to the global runtime data.
 * @return None.
 */
void	init_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "miniRT");
	if (!data->win)
		exit(1);
#ifdef __linux__
	x11_cap_window_max(data->mlx, data->win, WIN_W, WIN_H);
#endif
}

/**
 * @brief Allocate the render image and cache its pixel buffer metadata.
 * @param data Pointer to the global runtime data.
 * @return None.
 */
void	init_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (!data->img.img)
		exit(1);

	data->img.addr = mlx_get_data_addr(
		data->img.img,
		&data->img.bpp,
		&data->img.line_len,
		&data->img.endian
	);
}
