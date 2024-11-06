/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:34:16 by smejia-a          #+#    #+#             */
/*   Updated: 2024/11/02 15:05:35 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>

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
char	*ft_apply_min_field_int(char *str, char *s, int num, size_t min_field);
char	*ft_unsig_int(char *s, va_list args);
char	*ft_hexa_num_lower(char *s, va_list args);
char	*ft_hexa_num_upper(char *s, va_list args);

int		ft_create_character_arg(const char *s, va_list args, char **arg);

//Funciones del libft
int		ft_strcontains(const char *str, char c);
int		ft_isdigit(int c);
size_t	ft_strlen(char *str);
void	*ft_memset(void *ptr, int value, size_t num);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);
void	ft_strtoupper(void *str);
int		ft_toupper(int c);
void	ft_putchar(char c);
void	ft_putstr(char *str);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_intlen(int n, int base);
int		ft_abs(int num);
void	ft_bzero(void *ptr, size_t num);
char	*ft_strrchr(const char *s, int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
