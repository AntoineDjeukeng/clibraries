/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 06:52:12 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/10 21:35:56 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_insert_pos_from_head(t_stack *b, int ch)
{
	int		count;
	t_node	*tmp;

	count = 0;
	tmp = b->head;
	while (tmp && tmp->next)
	{
		if (tmp->target_index < ch && tmp->next->target_index > ch)
			return (count + 1);
		if (tmp->target_index > tmp->next->target_index)
		{
			if (ch > tmp->target_index || ch < tmp->next->target_index)
				return (count + 1);
		}
		tmp = tmp->next;
		count++;
	}
	return (0);
}

int	get_insert_pos_from_tail(t_stack *b, int ch)
{
	int		count;
	t_node	*tmp;

	count = 0;
	tmp = b->tail;
	while (tmp && tmp->prev)
	{
		if (tmp->prev->target_index < ch && tmp->target_index > ch)
			return (count + 1);
		if (tmp->prev->target_index > tmp->target_index)
		{
			if (ch > tmp->prev->target_index || ch < tmp->target_index)
				return (count + 1);
		}
		tmp = tmp->prev;
		count++;
	}
	return (0);
}

int	ft_dir_tail(t_stack *b, int p)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = b->tail;
	while (tmp && tmp->target_index != p)
	{
		i++;
		tmp = tmp->prev;
	}
	return (i + 1);
}

int	ft_dir_head(t_stack *b, int p)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = b->head;
	while (tmp && tmp->target_index != p)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}



void	vsmart_pb(t_stack *a, t_stack *b)
{
	int	target;
	int	from_head;
	int	from_tail;

	if (!a || !a->head)
		return ;
	target = a->head->target_index;
	if (b && b->head)
	{
		from_head = get_insert_pos_from_head(b, target);
		from_tail = get_insert_pos_from_tail(b, target);
		if (from_head <= from_tail)
			while (from_head-- > 0)
				r(b);
		else
			while (from_tail-- > 0)
				rr(b);
	}
	if (b->min == -1 || target < b->min)
		b->min = target;
	p(b, a);
}



void	vsmart_pa(t_stack *a, t_stack *b)
{
	int	from_head;
	int	from_tail;

	if (!b || !b->head)
		return ;
	from_head = ft_dir_head(b, b->min);
	from_tail = ft_dir_tail(b, b->min);
	if (from_head <= from_tail)
		while (from_head-- > 0)
			r(b);
	else
		while (from_tail-- > 0)
			rr(b);
	while (b->head && b->head->target_index == a->tail->target_index + 1)
	{
		p(a, b);
		r(a);
	}
}


