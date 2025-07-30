/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 03:24:26 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:47:23 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_create_node(t_stack *s, int value, int index)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		s->state = 1;
		return ;
	}
	node->index = index;
	node->value = value;
	node->next = NULL;
	if (s->a == NULL)
	{
		s->a = node;
		s->t_a = node;
	}
	else
	{
		s->t_a->next = node;
		s->t_a = node;
	}
}

void	ft_index(t_stack *s)
{
	int	*tmp;
	int	i;
	int	target;

	i = 0;
	tmp = malloc(s->size * sizeof(int));
	if (!tmp)
		return ;
	while (i < s->size)
	{
		tmp[i] = s->values[i];
		i++;
	}
	ft_quicksort(tmp, 0, s->size - 1);
	i = 0;
	while (i < s->size)
	{
		target = 0;
		while (target < s->size && tmp[target] != s->values[i])
			target++;
		ft_create_node(s, s->values[i], target);
		i++;
	}
	free(tmp);
}

void	move_element(t_stack *s)
{
	t_move_data	m;

	if (s->b == NULL)
		return ;
	m.min_moves = INT_MAX;
	m.best_i = -1;
	m.b_len = list_length(s->b);
	m.a_len = list_length(s->a);
	m.i = 0;
	while (m.i < m.b_len)
	{
		evaluate_move(s, &m);
		if (m.moves < m.min_moves)
		{
			m.min_moves = m.moves;
			m.best_i = m.i;
			m.best_val = m.val;
			m.best_a_rot = m.a_rot;
			m.best_b_rot = m.b_rot;
		}
		m.i++;
	}
	rotate_both(s, m.best_a_rot, m.best_b_rot);
	pa(s);
}

t_bool	is_sorted_and_unique(int *values, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		if (values[i] >= values[i + 1])
			return (t_false);
		i++;
	}
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (values[i] == values[j])
				return (t_false);
			j++;
		}
		i++;
	}
	return (t_true);
}

void	evaluate_move(t_stack *s, t_move_data *m)
{
	m->val = value_at(s->b, m->i);
	m->target_pos = get_target_position(s, m->val);
	if (m->target_pos <= m->a_len / 2)
		m->a_rot = m->target_pos;
	else
		m->a_rot = m->target_pos - m->a_len;
	if (m->i <= m->b_len / 2)
		m->b_rot = m->i;
	else
		m->b_rot = m->i - m->b_len;
	if (m->a_rot < 0)
		m->abs_a = -m->a_rot;
	else
		m->abs_a = m->a_rot;
	if (m->b_rot < 0)
		m->abs_b = -m->b_rot;
	else
		m->abs_b = m->b_rot;
	if (m->abs_a > m->abs_b)
		m->moves = m->abs_a;
	else
		m->moves = m->abs_b;
}
