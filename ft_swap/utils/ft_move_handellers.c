/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_handellers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:35:28 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 06:35:59 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	get_target_position(t_stack *s, int value)
{
	int	len;
	int	i;
	int	prev_idx;
	int	prev;
	int	curr;

	if (s->a == NULL)
		return (0);
	len = list_length(s->a);
	i = 0;
	while (i < len)
	{
		if (i == 0)
			prev_idx = len - 1;
		else
			prev_idx = i - 1;
		prev = value_at(s->a, prev_idx);
		curr = value_at(s->a, i);
		if (prev < value && value <= curr)
			return (i);
		i++;
	}
	return (min_value_index(s->a));
}

void	repeat_rotate(t_stack *s, char stack_name, int count, int reverse)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (stack_name == 'a')
		{
			if (reverse)
				rra(s);
			else
				ra(s);
		}
		else
		{
			if (reverse)
				rrb(s);
			else
				rb(s);
		}
		i++;
	}
}

void	rotate_to_top(t_stack *s, char stack_name, int idx)
{
	t_node	*stack;
	int		len;

	if (stack_name == 'a')
		stack = s->a;
	else
		stack = s->b;
	len = list_length(stack);
	if (len == 0)
		return ;
	if (idx <= len / 2)
		repeat_rotate(s, stack_name, idx, 0);
	else
		repeat_rotate(s, stack_name, len - idx, 1);
}

void	bring_smallest_to_top(t_stack *s)
{
	int		min_val;
	int		min_index;
	int		i;
	t_node	*cur;

	if (!s || !s->a)
		return ;
	min_val = s->a->index;
	min_index = 0;
	i = 0;
	cur = s->a;
	while (cur)
	{
		if (cur->index < min_val)
		{
			min_val = cur->index;
			min_index = i;
		}
		cur = cur->next;
		i++;
	}
	if (min_index <= i / 2)
		repeat_rotate(s, 'a', min_index, 0);
	else
		repeat_rotate(s, 'a', i - min_index, 1);
}
