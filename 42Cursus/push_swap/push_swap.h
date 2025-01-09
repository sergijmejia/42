/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:50:35 by smejia-a          #+#    #+#             */
/*   Updated: 2025/01/09 14:02:03 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"

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

/*Funciones auxiliares*/

t_list	*ft_free_lst(t_list **lst);
int		check_error_str(char *str);
t_list	*create_list(t_list **lst, char *str);
int		ft_lstmin(t_list *lst);
int		ft_lstmax(t_list *lst);
int		check_error_lst(t_list *lst);
int		organized_lst(t_list *lst);

/*Funciones de movimiento*/

void	swap(t_list **lst);
void	swap_swap(t_list **lst_a, t_list **lst_b);
void	push(t_list **lst_a, t_list **lst_b);
void	rotate(t_list **lst);
void	rotate_rotate(t_list **lst_a, t_list **lst_b);
void	reverse_rotate(t_list **lst);
void	reverse_rotate_rotate(t_list **lst_a, t_list **lst_b);

/*Funciones count_moves*/
int		count_moves_a(t_list *lst, int pos, int dir);
int		count_moves_b(t_list *lst, int x, int moves);

/*Funciones do_moves*/
void	do_moves_a(t_list **a, t_list **b, t_mov_properties new_mov);
void	do_moves_b(t_list **a, t_list **b, t_mov_properties new_mov);

/*Funciones setters*/
int		set_direction_b(int moves_dir);
int		set_result(t_mov_properties *new_mov, int i);
int		set_direction_a(int old_direction_a, int result);
int		set_rotate(int old_rotate, int result);
int		set_pos(t_list **a, int old_pos, int result, int i);

/*Funcion min_move*/
void	min_move(t_list **a, t_list **b);

/*Funcion organize*/
void	organize(t_list **a, t_list **b);

/*Funcion push_swap*/
void	push_swap(t_list **a, t_list **b);

/*Funciones bonus*/
int		check_push_swap(t_list **a, t_list **b);
int		ft_ko(t_list **a, t_list **b);
int		ft_ok(t_list **a, t_list **b);
int		functions_two_len(t_list **a, t_list **b, char *str);
int		functions_three_len(t_list **a, t_list **b, char *str);

#endif
