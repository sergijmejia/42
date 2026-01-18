/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:30:10 by smejia-a          #+#    #+#             */
/*   Updated: 2025/12/01 17:11:32 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

/*vector struct*/
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

/*ray struct*/
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

/*add vectors a and b*/
t_vector	add_vector(t_vector a, t_vector.b)
{
	t_vector	add_result;
	
	if (!a || !b)
		return (NULL);
	add_result.x = a.x + b.x;
	add_result.y = a.y + b.y;
	add_result.z = a.z + b.z;
	return (add_result);
}

/*substract vector b to vector a*/
t_vector	sub_vector(t_vector a, t_vector b)
{
	t_vector	sub_result;

	if (!a || !b)
		return (NULL);
	sub_result.x = a.x - b.x;
	sub_result.y = a.y - b.y;
	sub_result.z = a.z - b.z;
	return (sub_result);
}

double	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector	cross_prod_result;

	if (!a || !b)
		return (NULL);
	cross_prod_result = (a.y * b.z) - (a.z * b.y);
}

/*vector module - is the lenght of the vector*/
double	vector_module(t_vector a)
{
	double	module;

	module = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (module);
}

/*vector normalization*/
t_vector	norm_vector(t_vector a)
{
	double	module;

	module = vector_module(a);
	a.x = a.x / module;
	a.y = a.y / module;
	a.z = a.z / module;
	return (a);
}
