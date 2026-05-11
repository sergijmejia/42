/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 20:38:15 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 20:38:17 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lighting.h"
#include "trace.h"
#include <math.h>

/**
 * @brief Resolve object color, replacing plane color with checker if enabled.
 * @param rec Hit record (must reference a plane for checker).
 * @return Object or checker color.
 */
t_color	checker_color(t_hit_rec *rec)
{
	t_rt_plane	*pl;
	int			ix;
	int			iz;
	double		sc;

	if (!rec->obj || rec->obj->type != OBJ_PLANE || !rec->obj->pl.checker)
		return (rec->color);
	pl = &rec->obj->pl;
	sc = pl->ch_scale;
	if (sc < 1e-6)
		sc = 1.0;
	ix = (int)floor(rec->p.x / sc);
	iz = (int)floor(rec->p.z / sc);
	if (((ix + iz) & 1) == 0)
		return (pl->color);
	return (pl->ch_alt);
}
