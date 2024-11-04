/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:34:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/04 01:55:35 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "libft.h"
# include <stdio.h>

int		ft_printf(const char *s, ...);

size_t	ft_cal_min_field(char *s);
size_t	ft_cal_prec(char *s);
size_t	ft_count_arg_len(const char *s);
char	*ft_create_arg(const char *s, va_list args);
int		ft_flag(char *s, char c);
int		ft_numlen(unsigned long long n, int base);

char	*ft_character(char *s, va_list args);
char	*ft_string(char *s, va_list args);
char	*ft_hexa_pointer(char *s, va_list args);

char	*ft_integer(char *s, va_list args);
char	*ft_unsig_int(char *s, va_list args);
char	*ft_hexa_num_lower(char *s, va_list args);
char	*ft_hexa_num_upper(char *s, va_list args);

char	*ft_apply_min_field_int(char *str, char *s, int num, size_t min_field);
#endif
