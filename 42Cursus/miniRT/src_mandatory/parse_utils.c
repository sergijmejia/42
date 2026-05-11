/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:29:05 by smejia-a          #+#    #+#             */
/*   Updated: 2026/05/11 19:29:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
#include "libft.h"

/**
 * @brief Print a standard error line to stderr.
 * @param msg Explanatory message printed after the Error prefix.
 * @return Always 0 (used as parse failure flag by callers).
 */
int	put_error(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, "Error\n", 6);
	write(2, msg, len);
	write(2, "\n", 1);
	return (0);
}

/**
 * @brief Test for ASCII space or tab.
 * @param c Character to classify.
 * @return Non-zero if c is space or tab, otherwise 0.
 */
int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * @brief Count elements in a NULL-terminated string array.
 * @param split Array produced by ft_split.
 * @return Number of non-NULL pointers before the first NULL.
 */
int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

/**
 * @brief Free every string in a split array and the array itself.
 * @param split NULL-terminated array of allocated strings, or NULL.
 * @return None.
 */
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief Convert a decimal string to double (no exponent, basic subset).
 * @param str String starting with optional sign and digits, optional fraction.
 * @return Parsed double value.
 */
double	ft_atod(const char *str)
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
