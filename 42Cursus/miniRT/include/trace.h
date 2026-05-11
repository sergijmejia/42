/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:57:49 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 17:57:54 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "minirt.h"

int	trace_object_hit(t_object *o, t_vec ro, t_vec rd, t_hit_rec *rec);
int	trace_closest_skip(t_scene *scene, t_ray ray, t_hit_rec *out,
		t_object *skip);
int	trace_closest(t_scene *scene, t_vec ro, t_vec rd, t_hit_rec *out);

#endif
