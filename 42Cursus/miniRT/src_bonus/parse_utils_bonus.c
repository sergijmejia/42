/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:12:13 by rafaguti          #+#    #+#             */
/*   Updated: 2026/05/11 19:16:59 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "libft.h"

/**
 * @brief Parse decimal string to double (bonus parser helper).
 * @param str Numeric string.
 * @return Parsed value.
 */
double	bonus_atod(const char *str)
{
	double	num;
	double	dec;
	double	sign;

	num = 0.0;
	dec = 1.0;
	sign = 1.0;
	while (*str && is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1.0;
	while (*str && *str >= '0' && *str <= '9')
		num = num * 10.0 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		dec *= 10.0;
		num += (*str++ - '0') / dec;
	}
	return (num * sign);
}

/**
 * @brief Parse "x,y,z" vector for bonus elements.
 * @param str Comma-separated components.
 * @param v Output vector.
 * @return 1 on success, 0 on failure.
 */
int	bonus_parse_vec(char *str, t_vec *v)
{
	char	**xyz;

	xyz = ft_split(str, ',');
	if (!xyz || split_len(xyz) != 3)
		return (free_split(xyz), 0);
	v->x = bonus_atod(xyz[0]);
	v->y = bonus_atod(xyz[1]);
	v->z = bonus_atod(xyz[2]);
	free_split(xyz);
	return (1);
}
