/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 06:52:12 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/10 15:48:13 by adjeuken         ###   ########.fr       */
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

// int	get_insert_pos_from_head(t_stack *b, int ch)
// {
// 	int		count;
// 	t_node	*tmp;

// 	count = 0;
// 	tmp = b->head;
// 	while (tmp && tmp->next)
// 	{
// 		// Normal descending case: insert between two nodes
// 		if (tmp->target_index > ch && tmp->next->target_index < ch)
// 			return (count + 1);

// 		// Rotation break (e.g., max -> min)
// 		if (tmp->target_index < tmp->next->target_index)
// 		{
// 			if (ch < tmp->next->target_index || ch > tmp->target_index)
// 				return (count + 1);
// 		}
// 		tmp = tmp->next;
// 		count++;
// 	}
// 	return (0);
// }

// int	get_insert_pos_from_tail(t_stack *b, int ch)
// {
// 	int		count;
// 	t_node	*tmp;

// 	count = 0;
// 	tmp = b->tail;
// 	while (tmp && tmp->prev)
// 	{
// 		// Normal descending case: insert between two nodes
// 		if (tmp->prev->target_index > ch && tmp->target_index < ch)
// 			return (count + 1);

// 		// Rotation break (e.g., max -> min)
// 		if (tmp->prev->target_index < tmp->target_index)
// 		{
// 			if (ch < tmp->target_index || ch > tmp->prev->target_index)
// 				return (count + 1);
// 		}
// 		tmp = tmp->prev;
// 		count++;
// 	}
// 	return (0);
// }



int ft_dir_tail(t_stack *b, int p)
{
	int i=0;
	t_node *tmp = b->tail;
	while (tmp && tmp->target_index!=p)
	{
		i++;
		tmp=tmp->prev;
	}
	return i+1;
}

int ft_dir_head(t_stack *b, int p)
{
	int i=0;
	t_node *tmp = b->head;
	while (tmp && tmp->target_index!=p)
	{
		i++;
		tmp=tmp->next;
	}
	return i;
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
	if (!a || !a->head)
		return;

	int target = a->head->target_index;

	if (b && b->head)
	{
		int from_head = get_insert_pos_from_head(b, target);
		int from_tail = get_insert_pos_from_tail(b, target);

		if (from_head <= from_tail)
			while (from_head-- > 0)
				r(b);
		else
			while (from_tail-- > 0)
				rr(b);
	}
	if (b->min == -1 || target < b->min)
		b->min = target;
	// if((b->min!=-1 && a->head->target_index==0) )
	p(b, a);
}

void	rsmart_pb( t_stack *b)
{


	if (b && b->head)
	{
		int from_head = get_insert_pos_from_head(b, b->min);
		int from_tail = get_insert_pos_from_tail(b, b->min);
		if (from_head <= from_tail)
			while (from_head-- > 0)
				r(b);
		else
			while (from_tail-- > 0)
				rr(b);
	}
}

// void	vsmart_pb(t_stack *a, t_stack *b)
// {
// 	if (!a || !a->head)
// 		return;

// 	int target = a->head->target_index;

// 	if (b && b->head)
// 	{
// 		int from_head = get_insert_pos_from_head(b, target);
// 		int from_tail = get_insert_pos_from_tail(b, target);

// 		if (from_head <= from_tail)
// 			while (from_head-- > 0)
// 				r(b);
// 		else
// 			while (from_tail-- > 0)
// 				rr(b);
// 	}

// 	// Update b->max instead of min, if you track it
// 	if (b->min == -1 || target > b->min)
// 		b->min = target;

// 	p(b, a);
// }

void	vsmart_pa(t_stack *a, t_stack *b)
{
	int	from_head;
	int	from_tail;

	if (!b || !b->head)
		return;

	from_head = ft_dir_head(b, b->min);
	from_tail = ft_dir_tail(b, b->min);

	// Rotate b to bring min to top
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

	// Safely push elements to a in sorted order
	// while (
	// 	a->tail && (
	// 		(b->head && b->head->target_index == a->tail->target_index + 1) ||
	// 		(a->head && a->head->target_index == a->tail->target_index + 1)
	// 	)
	// )
	// {
	// 	if (b->head && b->head->target_index == a->tail->target_index + 1)
	// 	{
	// 		p(a, b);
	// 		if (b->head)
	// 			b->min = b->head->target_index;
	// 	}
	// 	r(a);
	// }
}



void ft_rb(t_stack *b, int p)
{
	int left;
	int right;

	left = ft_dir_tail(b,p);
	right = ft_dir_head(b,p);
	if(left>0 || right>0)
	{
		if(left>right)
		{
			while (left-->0)
				rr(b);
		}
		else
		{
			while (right-->0)
				r(b);
		}
	}

}

// void	vsmart_pb(t_stack *a, t_stack *b)
// {
// 	if (!a || !a->head)
// 		return;
// 	ft_rb(b,a->head->target_index);
// 	p(b, a);
// }
