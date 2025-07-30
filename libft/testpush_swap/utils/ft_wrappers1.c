/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrappers1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:16:03 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:46:55 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ra(t_stack *s)
{
	rotate(&(s->a), s, "ra\n");
}

void	rb(t_stack *s)
{
	rotate(&(s->b), s, "rb\n");
}

void	rra(t_stack *s)
{
	reverse_rotate(&(s->a), s, "rra\n");
}

void	rrb(t_stack *s)
{
	reverse_rotate(&(s->b), s, "rrb\n");
}
