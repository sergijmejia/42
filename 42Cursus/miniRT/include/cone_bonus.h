/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:56:47 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/02 17:56:51 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_BONUS_H
# define CONE_BONUS_H

# include "minirt.h"

t_hit	hit_cone_obj(t_vec ro, t_vec rd, t_rt_cone cn);
void	cone_norm_at(t_vec p, t_rt_cone cn, t_vec *n);
t_vec	cone_apex(t_rt_cone cn);
int     is_valid_u(t_vec ro, t_vec rd, t_rt_cone cn, double t);
int     hit_cone_side(t_vec ro, t_vec rd, t_rt_cone cn, double *out_t);
t_vec   cone_apex(t_rt_cone cn);

#endif
