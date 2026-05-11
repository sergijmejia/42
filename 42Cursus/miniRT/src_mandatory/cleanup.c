/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:33:00 by rafaguti          #+#    #+#             */
/*   Updated: 2026/04/29 21:05:00 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Free the light linked list on a scene (idempotent).
 * @param scene Scene whose lights pointer is cleared.
 * @return None.
 */
void	scene_lights_clear(t_scene *scene)
{
	t_light_node	*n;
	t_light_node	*nx;

	if (!scene)
		return ;
	n = scene->lights;
	while (n)
	{
		nx = n->next;
		free(n);
		n = nx;
	}
	scene->lights = NULL;
}

/**
 * @brief Free all allocated objects in the scene list.
 * @param scene Scene whose objects pointer is cleared.
 * @return None.
 */
void	scene_objects_clear(t_scene *scene)
{
	t_object	*obj;
	t_object	*next;

	if (!scene)
		return ;
	obj = scene->objects;
	while (obj)
	{
		next = obj->next;
		free(obj);
		obj = next;
	}
	scene->objects = NULL;
}

/**
 * @brief Release MLX resources and terminate the program.
 * @param data Pointer to runtime data with MLX resources.
 * @param exit_code Process exit status to return to shell.
 * @return Never returns in practice (exit is called).
 */
int	cleanup_and_exit(t_data *data, int exit_code)
{
	if (data)
	{
		scene_lights_clear(&data->scene);
		scene_objects_clear(&data->scene);
		if (data->img.img && data->mlx)
			mlx_destroy_image(data->mlx, data->img.img);
		if (data->win && data->mlx)
			mlx_destroy_window(data->mlx, data->win);
#ifdef __linux__
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
			data->mlx = NULL;
		}
#endif
	}
	exit(exit_code);
	return (0);
}
