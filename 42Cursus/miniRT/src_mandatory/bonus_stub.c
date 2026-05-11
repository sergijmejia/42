/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_stub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:01:01 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 18:01:10 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Mandatory build: reject duplicate light lines.
 * @param t Unused token line.
 * @param s Unused scene pointer.
 * @return Always 0 (parse failure for duplicate L).
 */
int	bonus_append_light(char **t, t_scene *s)
{
	(void)t;
	(void)s;
	return (0);
}

/**
 * @brief Mandatory build: cone identifier is not supported.
 * @param t Unused.
 * @param s Unused.
 * @return Always 0 (parse failure).
 */
int	bonus_add_cone(char **t, t_scene *s)
{
	(void)t;
	(void)s;
	return (0);
}

/**
 * @brief Mandatory build: checker planes are not parsed here.
 * @param t Unused.
 * @param s Unused.
 * @return Always -1 (not handled).
 */
int	bonus_try_checker_plane(char **t, t_scene *s)
{
	(void)t;
	(void)s;
	return (-1);
}
