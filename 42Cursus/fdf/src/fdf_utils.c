/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:05:59 by smejia-a          #+#    #+#             */
/*   Updated: 2025/03/27 12:09:49 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*Funcion para encontrar el valor maximo de un array de float*/
float	ft_max_float(float *cord, int len)
{
	float	max;
	int		i;

	max = cord[0];
	i = 0;
	while (i < len)
	{
		if (cord[i] > max)
			max = cord[i];
		i++;
	}
	return (max);
}

/*Funcion para encontrar el valor minimo de un array de flat*/
float	ft_min_float(float *cord, int len)
{
	float	min;
	int		i;

	min = cord[0];
	i = 0;
	while (i < len)
	{
		if (cord[i] < min)
			min = cord[i];
		i++;
	}
	return (min);
}

/*Funcion de libearacion de memoria del split*/
char	*ft_clean_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}
