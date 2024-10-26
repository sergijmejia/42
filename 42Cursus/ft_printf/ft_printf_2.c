/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:39:12 by smejia-a          #+#    #+#             */
/*   Updated: 2024/10/18 11:58:15 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft.h"

int	countsplitlen(const char *s, t_list **lst)
{
	int	nodo;
	int	possible_arg;
	char	*start;
	t_list	new_node;
	char	*str;

	nodo = 0;
	possible_arg = 0;
	start = NULL;
	*lst = NULL;
	while (*s)
	{
		printf("Esta evaluando %c, el valor de nodo es: %d, possible_arg es: %d\n", *s, nodo, possible_arg);
		if ((*s != '%') && (!start) && (!possible_arg))
			start = (char *)s;
		else if ((*s != '%') && (!start) && (possible_arg))
		{
			if (ft_strcontains("cspdiuxX", *s))
			{
				possible_arg = 0;
				str = (char *) malloc (2 + 1);
				if (!str)
				{
					free(str);
					ft_lstclear(lst, free);
					return (-1);
				}
				ft_strlcpy(str, s - 1, ft_strlen(str));
				ft_lstadd_back(lst, ft_lstnew(str));
				str = NULL;
				nodo++;
			}
			else
			{
				ft_lstclear(lst, free);
				return (-1);
			}
		}
		else if ((*s != '%') && (start) && (possible_arg))
		{
			if (ft_strcontains("cspdiuxX", *s))
			{
				str = (char *) malloc (s - start + 1);
				if (!str)
				{
					free(str);
					ft_lstclear(lst, free);
					return (-1);
				}
				ft_strlcpy(str, start, ft_strlen(str));
				ft_lstadd_back(lst, ft_lstnew(str));
				str = NULL;
				nodo++;
				str = (char *) malloc (2 + 1);
				if (!str)
				{
					free(str);
					ft_lstclear(lst, free);
					return (-1);
				}
				ft_strlcpy(str, s - 1, ft_strlen(str));
				ft_lstadd_back(lst, ft_lstnew(str));
				str = NULL;
				nodo++;
				possible_arg = 0;
				start = NULL;
			}
			else
			{
				ft_lstclear(lst, free);
				return (-1);
			}
		}
		else if ((*s == '%') && (!start) && (!possible_arg))
			possible_arg = 1;
		else if ((*s == '%') && (!start) && (possible_arg))
		{
			possible_arg = 0;
			start = (char *) s -1;
		}
		else if ((*s == '%') && (start) && (!possible_arg))
			possible_arg = 1; 
		else if ((*s == '%') && (start) && (possible_arg))
			possible_arg = 0;
		s++;
	}
	if (possible_arg)
	{
		ft_lstclear(lst, free);
		return (-1);
	}
	if (start)
	{
		str = (char *) malloc (s - start + 1);
		if (!str)
		{
			free(str);
			ft_lstclear(lst, free);
			return (-1);
		}
		ft_strlcpy(str, start, ft_strlen(str));
		ft_lstadd_back(lst, ft_lstnew(str));
		str = NULL;
		nodo++;
	}
	printf("La longitud de la variable nodo es: %d\n", nodo);
	return (ft_lstsize(*lst));
}

int	ft_printf(const char *s, ...)
{
	va_list	var;
	t_list	**split;

	strlen = ft_strlen(str);
	va_start(var, s);

		
}

int	main(int argc, char *argv[])
{
	int		var;
	t_list	**lst;

	if (argc != 2)
	{
		printf("Cantidad de argumentos incorrecta\n");
		return (1);
	}
	lst = (t_list **) malloc (sizeof(t_list *));
	var = countsplitlen(argv[1], lst) + 55;
	//printf("El valor de var es: %d\n", var);
	
	printf("%l Este es un texto de prueba %u para probar la funcion %d %d %d %d %d %d contvariables", var);
	ft_lstclear(lst, free);
	free(lst);
	return (0);
}
