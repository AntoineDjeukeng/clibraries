/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:40:55 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 11:11:05 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	apply_operation(const char *op, t_stack *s)
{
	if ((ft_strcmp(op, "sa\n") == 0))
		sa(s);
	else if ((ft_strcmp(op, "ss\n") == 0))
		ss(s);
	else if ((ft_strcmp(op, "sb\n") == 0))
		sb(s);
	else if ((ft_strcmp(op, "pa\n") == 0))
		pa(s);
	else if ((ft_strcmp(op, "pb\n") == 0))
		pb(s);
	else if ((ft_strcmp(op, "ra\n") == 0))
		ra(s);
	else if ((ft_strcmp(op, "rb\n") == 0))
		rb(s);
	else if ((ft_strcmp(op, "rr\n") == 0))
		rr(s);
	else if ((ft_strcmp(op, "rra\n") == 0))
		rra(s);
	else if ((ft_strcmp(op, "rrb\n") == 0))
		rrb(s);
	else if ((ft_strcmp(op, "rrr\n") == 0))
		rrr(s);
	else
		s->state = 4;
}

void	ft_is_sorted_bounus(t_stack *s)
{
	int		i;
	t_node	*tmp;

	tmp = s->a;
	i = tmp->index;
	while (tmp)
	{
		if (tmp->index < i)
			return ;
		tmp = tmp->next;
	}
	s->state = 1;
	s->is_sorted = 1;
}

void	ft_check_results(t_stack *s)
{
	int	i;

	i = 0;
	while (i < s->op_count)
	{
		if (s->ops[i] && s->state != 4)
			apply_operation(s->ops[i], s);
		i++;
	}
	if (s->state == 4)
	{
		s->state = 1;
		s->is_sorted = 0;
		s->v_is_sorted = 0;
	}
	if (s->state != 1)
	{
		s->is_sorted = 0;
		ft_is_sorted_bounus(s);
	}
}
