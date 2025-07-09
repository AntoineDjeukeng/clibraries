/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 06:52:12 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/09 19:44:36 by adjeuken         ###   ########.fr       */
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

int	ft_min_distance(t_stack *b, int ch)
{
	int	direct;
	int	indirect;

	direct = get_insert_pos_from_head(b, ch);
	indirect = get_insert_pos_from_tail(b, ch);
	if (direct <= indirect)
		return (direct);
	else
		return (-indirect);
}

void	vsmart_pb(t_stack *a, t_stack *b)
{
	int	from_haed;
	int	from_tail;
	int findex;
	findex = a->head->target_index;
	if (!a || !a->head)
		return ;

	if(b && b->min=a->head->target_index+1)
	{
		from_haed = get_insert_pos_from_head(b, a->head->target_index);
		from_tail = get_insert_pos_from_tail(b, a->head->target_index);
		if (from_haed <= from_tail)
		{
			while (from_haed-- > 0)
				r(b);
		}
		else
		{
			while (from_tail-- > 0)
				rr(b);
		}
		while ()
		{
			/* code */
		}
		


	}
	if (b->head)
	{
		from_haed = get_insert_pos_from_head(b, findex);
		from_tail = get_insert_pos_from_tail(b, findex);
		if (from_haed <= from_tail)
		{
			while (from_haed-- > 0)
				r(b);
		}
		else
		{
			while (from_tail-- > 0)
				rr(b);
		}
	}
	if (b->min > a->head->target_index || b->min == -1)
		b->min = a->head->target_index;
	p(b, a);
}


void	vsmart_pa(t_stack *a, t_stack *b)
{
	int	from_haed;
	int	from_tail;

	if (!b || !b->head)
		return ;


	from_haed = get_insert_pos_from_head(b, b->min);
	from_tail = get_insert_pos_from_tail(b, b->min);
	if (a->head)
	{
		if (from_haed <= from_tail)
		{
			printf("\n -%d- \n",from_haed);
			while (from_haed-- >= 0)
				r(b);
		}
		else
		{
			printf("\n -%d- \n",from_tail);
			while (from_tail-- > 0)
				rr(b);
		}
		while (b->head && b->head->target_index == a->head->target_index+1)
		{
			p(a, b);
			printf("\n ll-%d- \n",2);
			a->min = b->head->next->target_index;
			rr(a);
		}


	}
}
