/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:21:10 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/24 22:35:46 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include <limits.h>
#include <poll.h>

int					ft_process_input(const int count, const char **str,
						int *numbers);
long				ft_atol(const char *str);
int					ft_isspace(char c);
int					ft_try_parse_int(const char *str, int *out);

#define MAX_SIZE 200000

typedef struct s_node
{
	int				value;
	int				r_value;
	char			name;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node			*a;
	t_node			*b;
	t_node			*t_a;
	t_node			*t_b;
	char			*ops[MAX_SIZE];
	int				op_count;
	int				size;
	int				keys[MAX_SIZE];
	int				indexes[MAX_SIZE];
	int				index_size;
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
void				evaluate_move(t_stack *s, t_move_data *m);
void				rotate_both(t_stack *s, int a_rot, int b_rot);
void				sort(t_stack *s);
void				init_stack(t_stack *s, int *values);
void				ft_create_node(t_node **head, int value, int index);
void				reverse_rotate(t_node **s, t_stack *stack,
						const char *name);
void				rotate(t_node **s, t_stack *stack, const char *name);
void				swap(t_node **s, t_stack *stack, const char *name);
void				push(t_node **src, t_node **dst, t_stack *s,
						const char *name);
void				rrr(t_stack *s);
void				rr(t_stack *s);
void				rotate_to_top(t_stack *s, char stack_name, int idx);
int					get_target_position(t_stack *s, int value);
void				ft_quicksort(int arr[], int low, int high);
void				bring_smallest_to_top(t_stack *s);
int					value_at(t_node *head, int idx);
void				ra(t_stack *s);
void				rb(t_stack *s);
void				rra(t_stack *s);
void				rrb(t_stack *s);
void				sa(t_stack *s);
void				sb(t_stack *s);
void				ss(t_stack *s);
void				pa(t_stack *s);
void				pb(t_stack *s);
int					list_length(t_node *head);
int					min_value_index(t_node *head);
int					ft_is_sorted(int *array, int size);
int		apply_operation(const char *op, t_stack *s);
void				evaluate_move(t_stack *s, t_move_data *m);
long				ft_atol(const char *str);
void				ft_check_results(t_stack *s);
void				move_element(t_stack *s);
int	ft_input_str(char *str);
void ft_error();
