/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:23:26 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/13 05:09:28 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_both_negative(Stack *s, int a_rot, int b_rot)
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

void	rotate_both(Stack *s, int a_rot, int b_rot)
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

void	rr(Stack *s)
{
	if (s->a && s->b)
	{
		rotate(&(s->a), s, "ra");
		rotate(&(s->b), s, "rb");
		s->op_count -= 2;
		s->ops[s->op_count++] = strdup("rr");
	}
}

void	rrr(Stack *s)
{
	if (s->a && s->b)
	{
		reverse_rotate(&(s->a), s, "rra");
		reverse_rotate(&(s->b), s, "rrb");
		s->op_count -= 2;
		s->ops[s->op_count++] = strdup("rrr");
	}
}
