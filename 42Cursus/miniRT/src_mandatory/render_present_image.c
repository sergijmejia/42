#include "minirt.h"

/**
 * @brief Copy the rendered MLX image to the window (call after init_window).
 * @param d Runtime and image data.
 * @return None.
 */
void	present_image(t_data *d)
{
	mlx_put_image_to_window(d->mlx, d->win, d->img.img, 0, 0);
}