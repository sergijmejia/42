/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_present_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:30:01 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:30:02 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
