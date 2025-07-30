/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:23:26 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:47:18 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate_both_negative(t_stack *s, int a_rot, int b_rot)
{
	while (a_rot < 0 && b_rot < 0)
	{
		rrr(s);
		a_rot++;
		b_rot++;
	}
	while (a_rot < 0)
	{
		rra(s);
		a_rot++;
	}
	while (b_rot < 0)
	{
		rrb(s);
		b_rot++;
	}
}

void	rotate_both(t_stack *s, int a_rot, int b_rot)
{
	while (a_rot > 0 && b_rot > 0)
	{
		rr(s);
		a_rot--;
		b_rot--;
	}
	while (a_rot > 0)
	{
		ra(s);
		a_rot--;
	}
	while (b_rot > 0)
	{
		rb(s);
		b_rot--;
	}
	if (a_rot < 0 || b_rot < 0)
		rotate_both_negative(s, a_rot, b_rot);
}

void	rrr(t_stack *s)
{
	if (s->a && s->b)
	{
		reverse_rotate(&(s->a), s, NULL);
		reverse_rotate(&(s->b), s, NULL);
		if (!s->bonus)
			s->ops[s->op_count++] = ft_strdup("rrr\n");
	}
}

void	rr(t_stack *s)
{
	if (s->a && s->b)
	{
		rotate(&(s->a), s, NULL);
		rotate(&(s->b), s, NULL);
		if (!s->bonus)
			s->ops[s->op_count++] = ft_strdup("rr\n");
	}
}

void	ss(t_stack *s)
{
	if (s->a && s->b)
	{
		swap(&(s->a), s, NULL);
		swap(&(s->b), s, NULL);
		if (!s->bonus)
			s->ops[s->op_count++] = ft_strdup("ss\n");
	}
}
