/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:46:49 by smejia-a          #+#    #+#             */
/*   Updated: 2026/01/13 18:46:51 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double  ft_atod(char *str)
{
    double  num;
    double  divisor;
    int     signo;
    int     i;

    num = 0;
    i = 0;
    signo = 1;
    while (str[i] && ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
        i++;
    if (str[i] == '-')
    {
        signo = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (str[i] != '\0' && str[i] != '.' && ft_isdigit(str[i]))
    {
        num = num * 10 + ((double) (str[i] - 48));
        i++;
    }
    if (str[i] == '.')
    {
        i++;
        divisor = 1;
        while (str[i] && ft_isdigit(str[i]))
        {
            divisor = divisor * 10;
            num = num + ((double) (str[i] - 48)) / divisor;
            i++;
        }
    }
    return (signo * num);
}
