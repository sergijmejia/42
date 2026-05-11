/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:20:00 by rafaguti          #+#    #+#             */
/*   Updated: 2026/04/29 21:05:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Start miniRT, parse scene input, and launch the MLX loop.
 * @param ac Argument count from command line.
 * @param av Argument vector from command line.
 * @return 0 on success, 1 on invalid arguments or parse failure.
 */
int	main(int ac, char **av)
{
	t_data	data;
	t_scene	scene;

	data.mlx = NULL;
	data.win = NULL;
	data.img.img = NULL;
	data.img.addr = NULL;
	if (ac != 2)
		return (1);
	if (!parse_rt_file(av[1], &scene))
		return (1);
	data.scene = scene;
	init_mlx(&data);
	init_image(&data);
	render_scene(&data);
	init_window(&data);
	present_image(&data);
	init_hooks(&data);

	mlx_loop(data.mlx);
	return (0);
}
