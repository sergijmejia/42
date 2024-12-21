/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:50:35 by smejia-a          #+#    #+#             */
/*   Updated: 2024/12/21 13:56:24 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft.h"

typedef struct s_properties
{
	int	dir_a;
	int	dir_b;
	int	pos;
	int	mov_a;
	int	mov_b;
	int	mov_b_dir;
	int	mov;
	int	rotate;
}	t_mov_properties;

#endif
