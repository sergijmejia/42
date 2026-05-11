/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:57:02 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/11 20:26:21 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "minirt.h"

int		shade_hit(t_data *d, t_hit_rec *rec, t_vec rd);
t_color	checker_color(t_hit_rec *rec);

#endif
