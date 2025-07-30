/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:52:10 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 11:14:01 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft/libft.h"
#include <limits.h>

typedef struct s_node
{
	int				index;
	int				value;
	char			name;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node			*a;
	t_node			*b;
	t_node			*t_a;
	t_node			*t_b;
	char			**ops;
	int				op_count;
	int				size;
	int				is_sorted;
	int				v_is_sorted;
	int				index_size;
	int				bonus;
	int				max_ops;
	int				state;
	int				*values;
	char			*line;
}					t_stack;
typedef struct s_move_data
{
	int				i;
	int				val;
	int				target_pos;
	int				a_rot;
	int				b_rot;
	int				abs_a;
	int				abs_b;
	int				moves;
	int				min_moves;
	int				best_i;
	int				best_val;
	int				best_a_rot;
	int				best_b_rot;
	int				a_len;
	int				b_len;
}					t_move_data;

t_stack				*ft_init_stack_list(int argc, char *argv[], int t);
void				ft_clean_stac(t_stack *s);
void				free_list(t_node *head);
int					ft_isspace(char c);
int					ft_try_parse_int(const char *str, int *out);
void				ft_is_duplicate(t_stack *s);
void				ft_is_sorted(t_stack *s);
void				ft_quicksort(int arr[], int low, int high);
void				ft_index(t_stack *s);
void				sort(t_stack *s);
void				move_element(t_stack *s);
t_bool				is_sorted_and_unique(int *values, int count);
void				evaluate_move(t_stack *s, t_move_data *m);
int					value_at(t_node *head, int idx);
int					list_length(t_node *head);
int					min_value_index(t_node *head);
int					get_target_position(t_stack *s, int value);
void				repeat_rotate(t_stack *s, char stack_name, int count,
						int reverse);
void				rotate_to_top(t_stack *s, char stack_name, int idx);
void				bring_smallest_to_top(t_stack *s);
void				ra(t_stack *s);
void				rb(t_stack *s);
void				rra(t_stack *s);
void				rrb(t_stack *s);
void				rrr(t_stack *s);
void				rr(t_stack *s);
void				sa(t_stack *s);
void				sb(t_stack *s);
void				ss(t_stack *s);
void				pa(t_stack *s);
void				pb(t_stack *s);
void				rotate_both(t_stack *s, int a_rot, int b_rot);
void				rotate(t_node **s, t_stack *stack, const char *name);
void				reverse_rotate(t_node **s, t_stack *stack,
						const char *name);
void				swap(t_node **s, t_stack *stack, const char *name);
void				push(t_node **src, t_node **dst, t_stack *s,
						const char *name);
void				ft_error(void);
void				ft_r(int r);
void				apply_operation(const char *op, t_stack *s);
void				ft_get_first_line(t_stack *s);

void				ft_is_sorted_bounus(t_stack *s);
void				ft_check_results(t_stack *s);
